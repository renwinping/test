#!/usr/bin/env python
#encoding=utf-8


import json
import time
import pycurl
import cStringIO
import gzip
import unicodedata
import os
import random

from time import strftime, localtime
from datetime import timedelta, date
import calendar



__author__ = 'rong'



user_agent_list = [
        "Mozilla/5.0 (Windows NT 6.1; WOW64) AppleWebKit/537.1 "
        "(KHTML, like Gecko) Chrome/22.0.1207.1 Safari/537.1",
        "Mozilla/5.0 (X11; CrOS i686 2268.111.0) AppleWebKit/536.11 "
        "(KHTML, like Gecko) Chrome/20.0.1132.57 Safari/536.11",
        "Mozilla/5.0 (Windows NT 6.1; WOW64) AppleWebKit/536.6 "
        "(KHTML, like Gecko) Chrome/20.0.1092.0 Safari/536.6",
        "Mozilla/5.0 (Windows NT 6.2) AppleWebKit/536.6 "
        "(KHTML, like Gecko) Chrome/20.0.1090.0 Safari/536.6",
        "Mozilla/5.0 (Windows NT 6.2; WOW64) AppleWebKit/537.1 "
        "(KHTML, like Gecko) Chrome/19.77.34.5 Safari/537.1",
        "Mozilla/5.0 (X11; Linux x86_64) AppleWebKit/536.5 "
        "(KHTML, like Gecko) Chrome/19.0.1084.9 Safari/536.5",
        "Mozilla/5.0 (Windows NT 6.0) AppleWebKit/536.5 "
        "(KHTML, like Gecko) Chrome/19.0.1084.36 Safari/536.5",
        "Mozilla/5.0 (Windows NT 6.1; WOW64) AppleWebKit/536.3 "
        "(KHTML, like Gecko) Chrome/19.0.1063.0 Safari/536.3",
        "Mozilla/5.0 (Windows NT 5.1) AppleWebKit/536.3 "
        "(KHTML, like Gecko) Chrome/19.0.1063.0 Safari/536.3",
        "Mozilla/5.0 (Macintosh; Intel Mac OS X 10_8_0) AppleWebKit/536.3 "
        "(KHTML, like Gecko) Chrome/19.0.1063.0 Safari/536.3",
        "Mozilla/5.0 (Windows NT 6.2) AppleWebKit/536.3 "
        "(KHTML, like Gecko) Chrome/19.0.1062.0 Safari/536.3",
        "Mozilla/5.0 (Windows NT 6.1; WOW64) AppleWebKit/536.3 "
        "(KHTML, like Gecko) Chrome/19.0.1062.0 Safari/536.3",
        "Mozilla/5.0 (Windows NT 6.2) AppleWebKit/536.3 "
        "(KHTML, like Gecko) Chrome/19.0.1061.1 Safari/536.3",
        "Mozilla/5.0 (Windows NT 6.1; WOW64) AppleWebKit/536.3 "
        "(KHTML, like Gecko) Chrome/19.0.1061.1 Safari/536.3",
        "Mozilla/5.0 (Windows NT 6.1) AppleWebKit/536.3 "
        "(KHTML, like Gecko) Chrome/19.0.1061.1 Safari/536.3",
        "Mozilla/5.0 (Windows NT 6.2) AppleWebKit/536.3 "
        "(KHTML, like Gecko) Chrome/19.0.1061.0 Safari/536.3",
        "Mozilla/5.0 (X11; Linux x86_64) AppleWebKit/535.24 "
        "(KHTML, like Gecko) Chrome/19.0.1055.1 Safari/535.24",
        "Mozilla/5.0 (Windows NT 6.2; WOW64) AppleWebKit/535.24 "
        "(KHTML, like Gecko) Chrome/19.0.1055.1 Safari/535.24" ]



class Day():
    def __init__(self):
        self.year = strftime("%Y", localtime())
        self.mon = strftime("%m", localtime())
        self.day = strftime("%d", localtime())
        self.hour = strftime("%H", localtime())
        self.min = strftime("%M", localtime())
        self.sec = strftime("%S", localtime())

    def today(self):
     '''''
     get today,date format="YYYY-MM-DD"
     '''''
     return date.today()


    def todaystr(self):
     '''
     get date string, date format="YYYYMMDD"
     '''
     return self.year + self.mon + self.day


    def datetime(self):
     '''''
     get datetime,format="YYYY-MM-DD HH:MM:SS"
     '''
     return strftime("%Y-%m-%d %H:%M:%S", localtime())


    def datetimestr(self):
     '''''
     get datetime string
     date format="YYYYMMDDHHMMSS"
     '''
     return self.year + self.mon + self.day + self.hour + self.min + self.sec


    def get_day_of_day(self, n=0):
     '''''
     if n>=0,date is larger than today
     if n<0,date is less than today
     date format = "YYYY-MM-DD"
     '''
     if (n < 0):
      n = abs(n)
      return date.today() - timedelta(days=n)
     else:
      return date.today() + timedelta(days=n)


    def get_days_of_month(self, year, mon):
     '''''
     get days of month
     '''
     return calendar.monthrange(year, mon)[1]


    def get_firstday_of_month(self, year, mon):
     '''''
     get the first day of month
     date format = "YYYY-MM-DD"
     '''
     days = "01"
     if (int(mon) < 10):
      mon = "0" + str(int(mon))
     arr = (year, mon, days)
     return "-".join("%s" % i for i in arr)


    def get_lastday_of_month(self, year, mon):
     '''''
     get the last day of month
     date format = "YYYY-MM-DD"
     '''
     days = calendar.monthrange(year, mon)[1]
     mon = self.addzero(mon)
     arr = (year, mon, days)
     return "-".join("%s" % i for i in arr)


    def get_firstday_month(self, n=0):
     '''''
     get the first day of month from today
     n is how many months
     '''
     (y, m, d) = self.getyearandmonth(n)
     d = "01"
     arr = (y, m, d)
     return "-".join("%s" % i for i in arr)


    def get_lastday_month(self, n=0):
     '''''
     get the last day of month from today
     n is how many months
     '''
     return "-".join("%s" % i for i in self.getyearandmonth(n))


    def getyearandmonth(self, n=0):
     '''''
     get the year,month,days from today
     befor or after n months
     '''
     thisyear = int(self.year)
     thismon = int(self.mon)
     totalmon = thismon + n
     if (n >= 0):
      if (totalmon <= 12):
       days = str(self.get_days_of_month(thisyear, totalmon))
       totalmon = self.addzero(totalmon)
       return (self.year, totalmon, days)
      else:
       i = totalmon / 12
       j = totalmon % 12
       if (j == 0):
        i -= 1
        j = 12
       thisyear += i
       days = str(self.get_days_of_month(thisyear, j))
       j = self.addzero(j)
       return (str(thisyear), str(j), days)
     else:
      if ((totalmon > 0) and (totalmon < 12)):
       days = str(self.get_days_of_month(thisyear, totalmon))
       totalmon = self.addzero(totalmon)
       return (self.year, totalmon, days)
      else:
       i = totalmon / 12
       j = totalmon % 12
       if (j == 0):
        i -= 1
        j = 12
       thisyear += i
       days = str(self.get_days_of_month(thisyear, j))
       j = self.addzero(j)
       return (str(thisyear), str(j), days)


    def addzero(self, n):
     '''''
     add 0 before 0-9
     return 01-09
     '''
     nabs = abs(int(n))
     if (nabs < 10):
      return "0" + str(nabs)
     else:
      return nabs


    def get_today_month(self,n=0):
     '''''
     获取当前日期前后N月的日期
     if n>0, 获取当前日期前N月的日期
     if n<0, 获取当前日期后N月的日期
     date format = "YYYY-MM-DD"
     '''
     (y, m, d) = self.getyearandmonth(n)
     arr = (y, m, d)
     if (int(self.day) < int(d)):
      arr = (y, m, self.day)
     return "-".join("%s" % i for i in arr)

def log_write(filename, str):
    file = open(filename, 'a')
    file.write(str)
    file.write('\n')
    file.flush()
    file.close()


#主要是针对chunked 模式，没办法搞
def curl_cmd_get(url):
    cmd = "curl '%s'" % (url)
    res = os.popen(cmd).read()
    return res

#1.0 版本不必支持chunked,
def httpGetContent(url, req_header=None, version = '1.1'):

    buf = cStringIO.StringIO()
    response_header = cStringIO.StringIO()
    c = pycurl.Curl()
    c.setopt(c.URL, url)
    c.setopt(c.WRITEFUNCTION, buf.write)
    c.setopt(c.CONNECTTIMEOUT, 10)
    c.setopt(c.TIMEOUT, 100)
    c.setopt(pycurl.MAXREDIRS, 5)
    c.setopt(pycurl.FOLLOWLOCATION, 1)

    if req_header is None:
        req_header = []


    flag = 0
    for key in req_header:
        if 'User-Agent:' in key or 'user-agent:' in key:
            flag = 1
            break

    if not flag:
        c.setopt(pycurl.USERAGENT, 'Mozilla/5.0 (Windows NT 6.1) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/60.0.3112.113 Safari/537.36')

    c.setopt(pycurl.TCP_NODELAY, 1)
    if '1.1' in version:
        add_headers = ['Accept:text/html,application/xhtml+xml,application/xml;q=0.9,image/webp,image/apng,*/*;q=0.8',
             'Connection:keep-alive','Accept-Language:zh-CN,zh;q=0.8,en;q=0.6','Cache-Control:max-age=0',
             'DNT:1','Upgrade-Insecure-Requests:1','Accept-Charset: utf-8']
        c.setopt(pycurl.ENCODING, 'gzip, deflate')
    else:
        add_headers = ['Accept:text/html,application/xhtml+xml,application/xml;q=0.9,image/webp,image/apng,*/*;q=0.8',
             'Connection:close','Accept-Language:zh-CN,zh;q=0.8,en;q=0.6','Cache-Control:max-age=0']
        c.setopt(pycurl.HTTP_VERSION, pycurl.CURL_HTTP_VERSION_1_0)
    if len(req_header):
        add_headers.extend(req_header)

    c.setopt(c.HTTPHEADER, add_headers)
    c.setopt(pycurl.HTTPGET, 1)
    c.setopt(c.HEADERFUNCTION, response_header.write)
    res = {}

    try:
        c.perform()
        str_head = '%s' % (response_header.getvalue())
        str_body = '%s' % (buf.getvalue())
        res['head'] = str_head
        res['body'] = str_body
        #print str_head, str_body
    except pycurl.error, error:
        errno, errstr = error
        print 'An error occurred: ', errstr, url
    c.close()
    buf.close()
    response_header.close()
    #print res
    return res

def GzipStream(streams):
    "用于处理容启动gzip压缩"
    if streams:
        data = cStringIO.StringIO(streams)
        g = gzip.GzipFile('', 'rb', 9, data)
        return g.read()

#
#成交明细
def get_stockid_detail(id, date):
    url = 'http://market.finance.sina.com.cn/downxls.php?date=%s&symbol=%s' % (date, id)
    res = httpGetContent(url)
    file_object = open('%s_%s_detail' % (id, date), 'w')
    file_object.write(res)
    file_object.close( )

#查看每股财务指标
def get_stockid_mgzb(id, req_header=None):
    if req_header is None:
        req_header = []

    url = 'http://comdata.finance.gtimg.cn/data/mgzb/%s' % (id)
    refer = 'http://stock.finance.qq.com/corp1/cwfx.html?mgzb-%s' %(id)

    req_header.extend(['Referer: %s' % (refer)])
    tmp_header = req_header
    i = 0
    imax = 3
    while 1:
        try:
            if i + 1 < imax:
                res = httpGetContent(url, req_header)
                value = res['body'].decode("gbk").split('=')[1].strip(';\r\n')
            else:
                res = curl_cmd_get(url)
                value = res.decode("gbk").split('=')[1].strip(';\r\n')

            id_dic= json.loads(value)
            break
        except Exception,e:
            #print url, value, e
            req_header = tmp_header
            req_header.extend(['User-Agent: %s' % (user_agent_list[random.randint(0, len(user_agent_list))])])
            i = i+1
            if i >= imax:
                log_write('errcode', id)
                break
            time.sleep(random.randint(1, 3))

    if i > imax:
        return  {}

    return id_dic['data']['mgzb']

#查看每股盈利能力
def get_stockid_ylnl(id, req_header=None):
    if req_header is None:
        req_header = []
    url = 'http://comdata.finance.gtimg.cn/data/ylnl/%s' % (id)
    refer = 'http://stock.finance.qq.com/corp1/cwfx.html?ylnl-%s' %(id)

    req_header.extend(['Referer: %s' % (refer)])
    tmp_header = req_header
    i = 0
    imax = 3
    while 1:
        try:
            if i + 1 < imax:
                res = httpGetContent(url, req_header)
                value = res['body'].decode("gbk").split('=')[1].strip(';\r\n')
            else:
                res = curl_cmd_get(url)
                value = res.decode("gbk").split('=')[1].strip(';\r\n')

            id_dic= json.loads(value)
            break
        except Exception,e:
            #print url, value, e
            req_header = tmp_header
            req_header.extend(['User-Agent: %s' % (user_agent_list[random.randint(0, len(user_agent_list))])])
            i = i+1
            if i >= imax:
                log_write('errcode', id)
                break
            time.sleep(random.randint(1, 3))

    if i > imax:
        return  {}

    return id_dic['data']['ylnl']

#查看每股成长能力
def get_stockid_cznl(id, req_header=None):
    if req_header is None:
        req_header = []
    url = 'http://comdata.finance.gtimg.cn/data/cznl/%s' % (id)
    refer = 'http://stock.finance.qq.com/corp1/cwfx.html?cznl-%s' %(id)

    req_header.extend(['Referer: %s' % (refer)])
    tmp_header = req_header
    i = 0
    imax = 3
    while 1:
        try:
            if i + 1 < imax:
                res = httpGetContent(url, req_header)
                value = res['body'].decode("gbk").split('=')[1].strip(';\r\n')
            else:
                res = curl_cmd_get(url)
                value = res.decode("gbk").split('=')[1].strip(';\r\n')

            id_dic= json.loads(value)
            break
        except Exception,e:
            #print url, value, e
            req_header = tmp_header
            req_header.extend(['User-Agent: %s' % (user_agent_list[random.randint(0, len(user_agent_list))])])
            i = i+1
            if i >= imax:
                log_write('errcode', id)
                break
            time.sleep(random.randint(1, 3))

    if i > imax:
        return  {}

    return id_dic['data']['cznl']

#偿债及资本结构
def get_stockid_czzb(id, req_header=None):
    if req_header is None:
        req_header = []
    url = 'http://comdata.finance.gtimg.cn/data/czzb/%s' % (id)
    refer = 'http://stock.finance.qq.com/corp1/cwfx.html?czzb-%s' %(id)

    req_header.extend(['Referer: %s' % (refer)])
    tmp_header = req_header
    i = 0
    imax = 3
    while 1:
        try:
            if i + 1 < imax:
                res = httpGetContent(url, req_header)
                value = res['body'].decode("gbk").split('=')[1].strip(';\r\n')
            else:
                res = curl_cmd_get(url)
                value = res.decode("gbk").split('=')[1].strip(';\r\n')

            id_dic= json.loads(value)
            break
        except Exception,e:
            #print url, value, e
            req_header = tmp_header
            req_header.extend(['User-Agent: %s' % (user_agent_list[random.randint(0, len(user_agent_list))])])
            i = i+1
            if i >= imax:
                log_write('errcode', id)
                break
            time.sleep(random.randint(1, 3))

    if i > imax:
        return  {}

    return id_dic['data']['czzb']


#杜邦分析
def get_stockid_dbfx(id, req_header=None):
    if req_header is None:
        req_header = []
    url = 'http://comdata.finance.gtimg.cn/data/dbfx/%s' % (id)
    refer = 'http://stock.finance.qq.com/corp1/dbfx.html?%s' %(id)

    req_header.extend(['Referer: %s' % (refer)])
    tmp_header = req_header
    i = 0
    imax = 3
    while 1:
        try:
            if i + 1 < imax:
                res = httpGetContent(url, req_header)
                value = res['body'].decode("gbk").split('=')[1].strip(';\r\n')
            else:
                res = curl_cmd_get(url)
                value = res.decode("gbk").split('=')[1].strip(';\r\n')

            id_dic= json.loads(value)
            break
        except Exception,e:
            #print url, value, e
            req_header = tmp_header
            req_header.extend(['User-Agent: %s' % (user_agent_list[random.randint(0, len(user_agent_list))])])
            i = i+1
            if i >= imax:
                log_write('errcode', id)
                break
            time.sleep(random.randint(1, 3))

    if i > imax:
        return  {}

    return id_dic['data']['dbfx']


def get_single_analysis(id, req_header=None):
    if req_header is None:
        req_header = []

    url = 'http://stock.finance.qq.com/sstock/list/view/dadan.php?t=js&c=%s&max=100&p=1&opt=2&o=0' % (id)
    refer = 'http://stockhtm.finance.qq.com/sstock/quotpage/dadan.htm?c=%s' % (id)

    stocklist = []
    req_header.extend(['Referer: %s' % (refer)])
    tmp_header = req_header
    i = 0
    imax = 3
    while 1:
        try:
            if i + 1 < imax:
                res = httpGetContent(url, req_header)
                value = res['body'].decode("gbk").split('=')[1].strip(';\r\n')
            else:
                res = curl_cmd_get(url)
                value = res.decode("gbk").split('=')[1].strip(';\r\n')
            stocklist = value.split(',')[1]
            break
        except Exception,e:
            #print url, value, e
            req_header = tmp_header
            req_header.extend(['User-Agent: %s' % (user_agent_list[random.randint(0, len(user_agent_list))])])
            i = i+1
            if i >= imax:
                log_write('errcode', id)
                break
            time.sleep(random.randint(1, 3))

    if i > imax:
        return  {}

    #print stocklist
    stockdict = {}
    stockdict['s'] = 0
    stockdict['s'] = 0
    items = stocklist.split('^')
    for item in items:
        subitems = item.split('~')
        if len(subitems) >= 6:
            if 's' in subitems[5] or 'S' in subitems[5]:
                stockdict['s'] += int(subitems[3])
            elif 'b' in subitems[5] or 'B' in subitems[5]:
                stockdict['b'] += int(subitems[3])

    return stockdict

def get_money_flow(id, req_header=None):
    if req_header is None:
        req_header = []
    url = 'http://qt.gtimg.cn/q=ff_%s' % (id)
    refer = 'http://finance.qq.com/stock/sother/test_flow_stock_quotpage.htm'

    stocklist = []
    req_header.extend(['Referer: %s' % (refer)])
    tmp_header = req_header
    i = 0
    imax = 3
    while 1:
        try:
            if i + 1 < imax:
                res = httpGetContent(url, req_header)
                value = res['body'].decode("gbk").split('=')[1].strip(';\r\n')
            else:
                res = curl_cmd_get(url)
                value = res.decode("gbk").split('=')[1].strip(';\r\n')
            stocklist = value.split('~')
            if len(stocklist) < 10:
                print url
                time.sleep(1)
                continue
            break
        except Exception,e:
            #print url, value, e
            req_header = tmp_header
            req_header.extend(['User-Agent: %s' % (user_agent_list[random.randint(0, len(user_agent_list))])])
            i = i+1
            if i >= imax:
                log_write('errcode', id)
                break
            time.sleep(random.randint(1, 3))

    if i > imax:
        return  {}

    #print stocklist
    stockdict = {}
    stockdict['main_force'] = float(stocklist[3])

    if 'Etag:' in res['head']:
        stockdict['Etag']  = res['head'].split('Etag:')[1].strip()

    return stockdict

#实时行情
def get_stockid_real_time(id, req_header=None):
    #url = 'http://qt.gtimg.cn/q=%s' % (id)
    #favicon = 'http://qt.gtimg.cn/favicon.ico
    if req_header is None:
        req_header = []
    url = 'http://sqt.gtimg.cn/utf8/q=%s' % (id)
    favicon = 'http://sqt.gtimg.cn/favicon.ico'
    while 1:
        res = httpGetContent(url, req_header)
        if len(res) < 2:
            print url
            time.sleep(1)
        else:
            value = res['body'].split('=')[1].strip(';\n')
            stocklist = value.split('~')
            if len(stocklist) < 48:
                print url
                time.sleep(1)
                continue
            break
    #不知道是不是反爬虫， 先请求吧
    #httpGetContent(favicon, 'Referer: %s' % (url))
    #print stocklist
    stockdict = {}
    stockdict['id'] = id
    stockdict['code'] = stocklist[2]                           # 股票代码
    #stockdict['name'] = unicode(stocklist[1], 'gbk')  # 股票名称
    stockdict['last_closing'] = float(stocklist[4])    # 昨日收盘价格
    stockdict['start'] = float(stocklist[5])           # 开盘价格
    if stockdict['start'] <= 1:
        return {}
    stockdict['end'] = float(stocklist[3])             # 当前收盘价格（可以是当前价格）
    stockdict['high'] = float(stocklist[33])           # 最高价格
    stockdict['low'] = float(stocklist[34])            # 最低价格
    #stockdict['buyvol'] = int(stocklist[7])             # 外盘
    #stockdict['sellvol'] = int(stocklist[8])           # 内盘

    #stockdict['range_price'] = float(stocklist[31])    # 涨跌价格
    stockdict['range_percent'] = float(stocklist[32])  # 涨跌比%

    #stockdict['volume'] = int(stocklist[6])            # 成交量（手）
    #stockdict['total_price'] = int(stocklist[37])      # 成交额（万元）
    stockdict['change_rate'] = float(stocklist[38]) # 换手率
    stockdict['pe'] = float(stocklist[39])          # 市盈率
    stockdict['swing'] = float(stocklist[43])           # 振幅

    stockdict['pb'] = float(stocklist[46])              # 股票市净率
    stockdict['date'] = stocklist[30][:8]               # 时间
    stockdict['block'] = False if stockdict['start'] else True #股票是否停牌
    stockdict['circulation_market_value'] = float(stocklist[44])
    stockdict['total_value'] = float(stocklist[45])
    #stockdict['high_limit'] = float(stocklist[47])
    #stockdict['low_limit'] = float(stocklist[48])
    if 'Etag:' in res['head']:
        stockdict['Etag']  = res['head'].split('Etag:')[1].strip()

    return stockdict

#获取所有股票列表
def get_stock_list():
    #url = 'http://www.shdjt.com/js/lib/astock.js'
    url = 'http://www.ctxalgo.com/api/stocks'
    req_header = ['Cookie:session=eyJfaWQiOnsiIGIiOiJNMkZtTldJME1qSXpNR1UzWWpka01UYzRabUV6TURKbU5qTTJZemcwWWpjPSJ9fQ.DMYGJg.ReVb3XLAerXR30CUrOoeh9kW5ug']
    #req_header = []
    while 1:
        res = httpGetContent(url, req_header)
        if len(res) < 2:
            print url
            time.sleep(1)
        else:
            print res['head']
            break

    #print res
    id_dic= json.loads(res['body'])

    file = open('code_all', "w+")
    for key in id_dic:
        file.write(unicodedata.normalize('NFKD', key).encode('ascii','ignore'))
        file.write('\n')
        id_dic[key] = {}
        key = unicodedata.normalize('NFKD', key).encode('ascii','ignore')
        file.flush()

    file.close()
    return id_dic

#解禁列表, http 相应数据不全， chunked 的问题， 后边再处理吧
def get_outDxf_list(start, end, req_header=None):
    if req_header is None:
        req_header = []
    url = 'http://stock.finance.qq.com//sstock/list/view/dxf.php?c=0&b=%s&e=%s' % (start, end)
    refer = 'http://finance.qq.com/stock/dxfcx.htm?t=2&mn=%s&mx=%s' %(start, end)
    req_header.extend(['Referer: %s' % (refer)])
    print url
    res = curl_cmd_get(url)
    #print res
    #value = res.split('=')[1].strip(';\n').decode("utf-8","ignore")
    value = res.decode("gbk").split('=')[1].strip(';\r\n')
    #print value
    id_dic= json.loads(value)

    return id_dic


#去掉停牌等
def get_basic_list():
    id_dic = []
    if not os.path.isfile('code_all'):
        id_dic = get_stock_list()
    else:
        file = open("code_all")
        while 1:
            line = file.readline().strip()
            if not line:
                break
            id_dic.append(line)
        file.close()


    file = open('base_list', "w+")

    basic_dic = {}
    header = []
    flag = False
    for key in id_dic:
        res = get_stockid_real_time(key, header)
        if len(res) < 1:
            continue

        if 'Etag' in res:
            header = ['If-None-Match: %s' % (res['Etag'])]

        if res['block']:  #停牌
            continue

        #res['name'] = unicodedata.normalize('NFKD', id_dic[key]).encode('ascii','ignore')

        if res['circulation_market_value'] >= 300:
            continue

        if res['total_value'] >= 500:
            continue

        if res['pe'] > 90 or res['pe'] < 0:
            continue

        if res['end'] > 20 or res['end'] <= 2:
            continue

        res['mgzb'] = get_stockid_mgzb(key)
        if len(res['mgzb']) < 1:
            continue

        if '--' not in res['mgzb'][0]['tbmgsy'] and  float(res['mgzb'][0]['tbmgsy']) < 0.1:
            continue

        if '--' not in res['mgzb'][0]['mgxjll'] and float(res['mgzb'][0]['mgxjll']) < 0.05:
            continue

        res['cznl'] = get_stockid_cznl(key)
        if len(res['cznl']) < 1:
            continue
        #if float(res['cznl'][0]['yylr']) < 0:
        #    continue
        #
        #if float(res['cznl'][0]['jlr']) < 0:
        #    continue
        #
        #if float(res['cznl'][0]['yylr']) < 30:
        #    continue


        basic_dic[res['id']] = res

        file.write(res['code'])
        file.write('\t')
        file.write(res['id'])
        file.write('\t')
        file.write(str(res['end']))
        file.write('\t')
        file.write(str(res['pe']))
        file.write('\t')
        file.write(str(res['pb']))
        file.write('\t')
        file.write(str(res['circulation_market_value']))
        file.write('\t')
        file.write(str(res['total_value']))
        file.write('\t')
        file.write(res['mgzb'][0]['tbmgsy'])
        file.write('\t')
        file.write(res['mgzb'][0]['mgxjll'])
        file.write('\t')
        file.write(res['cznl'][0]['mgsy'])
        file.write('\t')
        file.write(res['cznl'][0]['mgxj'])
        file.write('\t')
        file.write(res['cznl'][0]['zysr'])
        file.write('\t')
        file.write(res['cznl'][0]['yylr'])
        file.write('\t')
        file.write(res['cznl'][0]['jlr'])
        file.write('\t')
        file.write(res['date'])

        file.write('\n')
        file.flush()

        #print res
        #break
    file.close()


def load_base_list():
    if not os.path.isfile('base_list'):
        get_basic_list()

    id_dic = {}
    file = open("base_list")
    while 1:
        line = file.readline().strip()
        if not line:
            break
        items = line.split('\t')
        if len(items) < 8:
            continue
        tmp_dic = {}
        tmp_dic['code'] = items[0]
        tmp_dic['id'] = items[1]
        tmp_dic['end'] = items[2]
        tmp_dic['pe'] = float(items[3])
        tmp_dic['pb'] = float(items[4])
        tmp_dic['circulation_market_value'] = float(items[5])
        tmp_dic['total_value'] = float(items[6])
        tmp_dic['tbmgsy'] = items[7].replace(',', '')
        tmp_dic['mgxjll'] = items[8].replace(',', '')
        tmp_dic['mgsy'] = items[9].replace(',', '')
        tmp_dic['mgxj'] = items[10].replace(',', '')
        tmp_dic['zysr'] = items[11].replace(',', '')
        tmp_dic['yylr'] = items[12].replace(',', '')
        tmp_dic['jlr'] = items[13].replace(',', '')
        tmp_dic['date'] = items[14]

        id_dic[items[1]] = tmp_dic

    file.close()
    return id_dic

def do_search_short():

    day = Day()

    start_day = '%s' % (day.get_day_of_day(-20))
    end_day = '%s' % (day.get_day_of_day(30))
    print start_day.replace('-', ''), end_day.replace('-', '')
    ban_list = get_outDxf_list(start_day.replace('-', ''), end_day.replace('-', ''))
    ban_dic = {}
    for key in ban_list:
        idstr = '%s' % key[0]
        #print idstr
        ban_dic[idstr] = ''

    id_dic = load_base_list()
    remove_ley = []
    for key in id_dic:
        #print id_dic[key]['zysr']
        if '--' not in id_dic[key]['zysr'] and float(id_dic[key]['zysr']) < 0:
            remove_ley.append(key)
            continue

        if '--' not in id_dic[key]['jlr'] and float(id_dic[key]['jlr']) < 0:
            remove_ley.append(key)
            continue

        if '--' not in id_dic[key]['mgsy'] and float(id_dic[key]['mgsy']) < 0:
            remove_ley.append(key)
            continue

        if '--' not in id_dic[key]['mgxj'] and float(id_dic[key]['mgxj'])< 0:
            remove_ley.append(key)
            continue

        if '--' not in id_dic[key]['tbmgsy'] and float(id_dic[key]['tbmgsy']) < 0.2:
            remove_ley.append(key)
            continue

        if id_dic[key]['code'] in ban_dic:
            remove_ley.append(key)
            continue


        #if id_dic[key]['tbmgsy'] > 60:
        #    remove_ley.append(key)
        #    continue

    print 'remove_ley.length',len(remove_ley)
    for key in remove_ley:
        id_dic.pop(key)


    #for key in id_dic:
    #    print id_dic[key]

    search_dic = {}
    header = []
    while 1:
        for key in id_dic:
            if id_dic[key].has_key('real_tag'):
                res = get_stockid_real_time(key, ['If-None-Match: %s' % (id_dic[key]['real_tag'])])
            else:
                res = get_stockid_real_time(key)

            if len(res) < 1:
                continue

            if 'Etag' in res:
                id_dic[key]['real_tag'] = res['Etag']

            if res['range_percent'] < -0.3 or  res['range_percent'] > 0.3:
                continue

            id_dic[key]['range_percent'] = res['range_percent']

            if res['swing'] < 2.0:
                continue

            id_dic[key]['swing'] = res['swing']

            if res['change_rate'] < 1.0:
                continue

            id_dic[key]['change_rate'] = res['change_rate']
            if res['end'] < res['low']:
                continue

            id_dic[key]['end'] = res['end']

            flag = False
            if res['end'] > res['low'] and abs(res['end'] - res['low']) >= 2* abs(res['end'] - res['start']):
                flag = True

            #if res['end'] > res['low']:
            #    print 'secrch ', res

            #print res

            if id_dic[key].has_key('money_tag'):
                money = get_money_flow(key, ['If-None-Match: %s' % (id_dic[key]['money_tag'])])
            else:
                money = get_money_flow(key)

            if not len(money):
                continue


            if not id_dic[key].has_key('main_force'):
                id_dic[key]['main_force'] = []
            if len(id_dic[key]['main_force']) and abs(id_dic[key]['main_force'] - id_dic[key]['main_force'][-1]) > 50:
                id_dic[key]['main_force'].append(money['main_force'])
            elif not len(id_dic[key]['main_force']):
                id_dic[key]['main_force'].append(money['main_force'])

            id_dic[key]['money_tag'] = money['Etag']

            if len(id_dic[key]['main_force']) > 2 and id_dic[key]['main_force'][0] < id_dic[key]['main_force'][-1]:
                if abs(id_dic[key]['main_force'][-1] - id_dic[key]['main_force'][0]) >= 100:
                    flag = True

            big_data = get_single_analysis(key)
            if len(big_data) and big_data['b'] > big_data['s']:
                flag = True

            if flag:
                search_dic[key] = id_dic[key]

            #print money

        for key in search_dic:
            print 'search res', search_dic[key]
        time.sleep(10)

#A股就是个坑， 技术指标低位了， 仍然可以再砸
#技术指标高位了， 有资金接盘仍然可以涨, 高位始终是危险
#压力如铁桶，支撑如窗户纸
#有连续的大单介入才介入， 低位大资金都不介入， 肯定有猫腻
#业绩好的，下跌， 大资金不介入， 肯定有什么利空， 业绩可以变脸
#买二--买五是大单， 而买1是小单， 下跌也不买， 明显还没有??
if __name__ == '__main__':
    do_search_short()
