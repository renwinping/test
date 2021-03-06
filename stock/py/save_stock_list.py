#!/usr/bin/env python
#coding=utf-8


from mysql import *
import sys, getopt,time


def is_in_list(item, out_list):
    #tmp = unicode(item, 'gb2312')
    for key in out_list:
        #if key in item:
        #keystr = unicode(key, 'gb2312')
        #if tmp.find(keystr) != -1:
        #print key, item
        if key in item:
            #print key, item, '123'
            return key

    return ''


def get_out_str(tmp_dict, out_list):
    sb = ''
    for key in out_list:
        if key in tmp_dict.keys():
            sb +='%s\t' % (tmp_dict[key])

    return sb

def job(line, fp, out_dict, out_list):

    items = line.split('\t')
    #print items
    count = 0
    tmp_dict = {}
    for item in items:
        item = item.decode('gbk').encode('utf-8')
        out_item = is_in_list(item, out_list)

        if out_item.strip():
            #print out_item
            out_dict[count] = out_item

        if count in out_dict.keys():
            tmp_dict[out_dict[count]] = item

        count += 1
    sb = get_out_str(tmp_dict, out_list)

    #print sb, count, len(out_list)
    if sb.strip() and count >= len(out_list):
        sb += '\n'
        fp.write(sb)



def is_num_by_except(num):
    try:
        int(num)
        return True
    except ValueError:
#        print "%s ValueError" % num
        return False

def createTable(db):
    sql = '''CREATE TABLE IF NOT EXISTS `stock_list` (
            `Id` INT(11) NOT NULL AUTO_INCREMENT,
            `stock_id` varchar(12) NOT NULL,
            `stock_name` varchar(50) NOT NULL,
            `stock_price` varchar(8) NOT NULL COMMENT '当前价格',
            `circulated_market_value` varchar(50) NOT NULL,
            `circulation_capital_stock` varchar(50) NOT NULL,
            `ratios` varchar(16) NOT NULL,
            `industry` varchar(50) NOT NULL,
            PRIMARY KEY (`Id`)
            ) ; '''
    db.exesql(sql)

def insertTable(db, line):
    items = line.split('\t')
    if len(items) < 7:
        return

    if not is_num_by_except(items[0]):
        return
    sql = '''insert into stock_list(stock_id, stock_name, stock_price, circulated_market_value, circulation_capital_stock, ratios, industry) values(%s, %s, %s, %s, %s, %s, %s);'''
    #param = (items[0].decode('gbk').encode('utf-8'), items[1].decode('gbk').encode('utf-8'),items[6].decode('gbk').encode('utf-8'), items[2].decode('gbk').encode('utf-8'), items[3].decode('gbk').encode('utf-8'), items[4].decode('gbk').encode('utf-8'), items[5].decode('gbk').encode('utf-8'))
    param = (items[0], items[1],items[6], items[2], items[3], items[4], items[5])

    db.execute(sql, param)

def truncate(db):
    sql = '''truncate table stock_list;'''
    db.exesql(sql)


def get_stock_list(filename):


    date = time.strftime('%Y%m%d',time.localtime(time.time()))
    saveFileName = '%s_stock_list' % (date)
    fp = open(saveFileName, 'w+')

    out_list = ['代码', '名称', '流通市值', '流通股本', '市盈', '行业', '现价']
    out_dict = {}
    for line in open(filename):
        line = line.strip()
        if not line:
            continue

        job(line, fp,out_dict, out_list)
    fp.close()

    return saveFileName

def main(argv):

    reload(sys)
    sys.setdefaultencoding("utf-8")
    try:
        opts, args = getopt.getopt(argv[1:], 'f:')
    except getopt.GetoptError, err:
        print str(err)
        sys.exit(2)

    FileName = ''
    for o,a in opts:
        #print o, a
        if o in '-f':
            FileName = a

    saveFileName = ''
    saveFileName = get_stock_list(FileName)

    db = MySQL('localhost','root','123456')
    db.selectDb('stock')

    createTable(db)

    #truncate(db)
    for line in open(saveFileName):
        line = line.strip()
        #print line
        if not line:
            continue

        insertTable(db, line)


if __name__ == '__main__':
    main(sys.argv)



