#!/usr/bin/env python
#coding=utf-8


from myLog import  *
from mysql import *
from runCpp import *
from runJava import *
from runPhp import *
from runJs import *
from runSwift import *
import os, time, base64


#工作目录
work_path = '/tmp/qf'
#makefile 目录
makefile_path = ''

pidSet = {}

run_time_out = 3 #3 秒
max_subPid_num = 2 #最大子进程数量

def getAnswerInfo(db, log):

    sql = '''select a.id as answerId, a.source_code as srcCode, a.language as language, a.exec_input, a.param, a.standard_output,
    b.input_file as inPutfileContent from student_program a,
    program_info b where a.program_id = b.id and a.status = "submit_ok" limit 1000;'''

    #log.debug("SQL:%s" %(sql))

    db.selectDb('qf_admin_online')

    res = db.select(sql)

    return res


def updateAnswerInfo(db, log, resultInfo):

    sql = '''UPDATE  student_program set status = '%s', exec_output = '%s' where id = '%s';''' % (db.escape_string(resultInfo['status']), db.escape_string(resultInfo['exec_output']), resultInfo['answerId'])

    log.debug("SQL:%s" % (sql))

    db.selectDb('qf_admin_online')
    db.exesql(sql)

def checkRunRes(db, log):
    for answerId in pidSet.keys():
        if getResToDb(db, log, pidSet[answerId]):
	        #print 'Del', answerId, pidSet
            del(pidSet[answerId])
	        #print 'AfterDel', pidSet


def checkRecordExist(answerid):
    flag = False
    #print pidSet, " ==> "

    if pidSet.has_key(answerid):
	    flag = True

    return flag

def checkOnlineSubpidNum():
    i = 0
    for answerId in pidSet.keys():
        item = pidSet[answerId]
        if checkProcessExist(item['subPid']):
            i = i + 1
    return i

def getResToDb(db, log, item):
    path = item['path']
    if not os.path.exists(path):
        if checkProcessExist(item['subPid']):
            return False
        else:
	        return True

    os.chdir(path)

    current_milli_time = getMilliSeconds()

    pid = item['subPid']
    if checkProcessExist(pid):
        if abs(current_milli_time - item['current_milli_time']) >= run_time_out * 1000:
            try:
		        #print 'kill ', pid
                os.kill(int(pid), signal.SIGKILL)
            except:
                return False
        else:
            return False


    item['status'] = ''
    item['status'] = getFileInfo(getStatusFileName(item['answerId']))

    if item['status'] == 'ok':
        item['exec_output'] = getFileInfo(getOutPutFileName(item['answerId']))
    else:
        item['exec_output']=getFileInfo(getOutPutFileName(item['answerId']))
        if not item['exec_output'].strip():
            item['exec_output'] = getFileInfo(getErrFileName(item['answerId']))
        if item['status'] == 'compile_ok':
            item['status'] = 'run_error'
    if not item['status'].strip():
	return True

    updateAnswerInfo(db, log, item)

    os.chdir(work_path)
    #if item['status'] == 'ok':
    cmd = 'rm -rf %s' % (item['answerId'])
    os.system(cmd)

    return True


def doJobs(db, log):

    tmpRes = []
    while 1:
        if len(pidSet) > 0:
            checkRunRes(db, log)

        res = getAnswerInfo(db,log)
        #print("doJobs ===> len = %u", len(res))

        if len(res) <= 0 or not cmp(tmpRes, res):
            time.sleep(run_time_out)
            continue

	    tmpRes = res



        for item in res:
	    print item, "hello world"

            if checkRecordExist(item['answerId']):
                continue

            while checkOnlineSubpidNum() >= max_subPid_num:
                checkRunRes(db, log)
                time.sleep(1)

            item['path'] = '''%s/%s''' % (work_path, item['answerId'])
            item['makefile_path'] = makefile_path

 	        #print os.getpid(), item['answerId'], item['answerId'], '__main__'
            pid = os.fork()
            if not pid:

                if  'cpp' in item['language']:
                    item['lang'] = 'gcc'
                    rCpp = RunCpp(log)
                    rCpp.buildAndrun(item)
                elif 'java' == item['language']:
                    item['lang'] = 'javac'
                    rJava = RunJava(log)
                    rJava.buildAndrun(item)
                elif 'php' in item['language']:
                    item['lang'] = 'php'
                    rPhp = RunPhp(log)
                    rPhp.buildAndrun(item)
                elif 'javascript' in item['language']:
                    item['lang'] = 'node'
                    rJs = RunJs(log)
                    rJs.buildAndrun(item)
                elif 'swift' in item['language']:
                    item['lang'] = 'swiftc'
                    rSwift = RunSwift(log)
                    rSwift.buildAndrun(item)

                sys.stdout.flush()

                os._exit(0)
            else:
                tmp = {}
                tmp['answerId'] = item['answerId']
                tmp['subPid'] = pid
                tmp['current_milli_time'] = getMilliSeconds()
                tmp['path'] = item['path']
                tmp['standard_output'] = item['standard_output']
                pidSet[item['answerId']] = tmp

                checkRunRes(db, log)



if __name__ == '__main__':

    makefile_path = '%s/%s' % (os.getcwd(), 'script')

    daemon = Daemon()
    daemon.daemonize()

    cmd = 'mkdir -p %s' % (work_path)
    os.system(cmd)
    os.chdir(work_path)

    logger = getLoger('qf')
    db = MySQL(logger, '115.28.35.83','qf_admin','5dxZM1b!uS')

    PATH = os.getenv('PATH')
    PATH = '%s:%s' % (PATH, '/home/yang/jdk1.8/bin')
    os.environ['PATH'] = PATH

    signal.signal(signal.SIGCHLD, signal.SIG_IGN)

    doJobs(db, logger)

