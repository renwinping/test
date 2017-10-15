#!/usr/bin/env python
#encoding=gbk

import urllib2
import json
import time


__author__ = 'rong'



#
#�ɽ���ϸ
def get_stockid_detail(id, date):
    url = 'http://market.finance.sina.com.cn/downxls.php?date=%s&symbol=%s' % (date, id)
    res = urllib2.urlopen(url).read()
    file_object = open('%s_%s_detail' % (id, date), 'w')
    file_object.write(res)
    file_object.close( )


#ʵʱ����
def get_stockid_real_time(id):

    user_agent = '"Mozilla/5.0 (Linux; Android 6.0; Nexus 5 Build/MRA58N) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/61.0.3163.100 Mobile Safari/537.36"'

    headers = { 'User-Agent' : user_agent }

    url = 'http://qt.gtimg.cn/q=%s' % (id)
    req = urllib2.Request(url, headers = headers)
    res=urllib2.urlopen(req).read()
    #res = urllib2.urlopen(url, headers = headers).read()
    value = res.split('=')[1]
    stocklist = value.split('~')
    stockdict = {}
    stockdict['id'] = id.decode("unicode_escape").encode("gbk")
    stockdict['code'] = stocklist[2]                           # ��Ʊ����
    #stockdict['name'] = unicode(stocklist[1], 'gbk')  # ��Ʊ����
    stockdict['last_closing'] = float(stocklist[4])    # �������̼۸�
    stockdict['start'] = float(stocklist[5])           # ���̼۸�
    stockdict['end'] = float(stocklist[3])             # ��ǰ���̼۸񣨿����ǵ�ǰ�۸�
    stockdict['high'] = float(stocklist[33])           # ��߼۸�
    stockdict['low'] = float(stocklist[34])            # ��ͼ۸�
    stockdict['buyvol'] = int(stocklist[7])             # ���� todo ���ݶԲ���
    stockdict['sellvol'] = int(stocklist[8])           # ���� todo ���ݶԲ���

    stockdict['range_price'] = float(stocklist[31])    # �ǵ��۸�
    stockdict['range_percent'] = float(stocklist[32])  # �ǵ���%

    stockdict['volume'] = int(stocklist[6])            # �ɽ������֣�
    stockdict['total_price'] = int(stocklist[37])      # �ɽ����Ԫ��
    stockdict['change_rate'] = float(stocklist[38]) # ������
    stockdict['pe'] = float(stocklist[39])          # ��ӯ��
    stockdict['swing'] = float(stocklist[43])           # ���

    stockdict['pb'] = float(stocklist[46])              # ��Ʊ�о���
    stockdict['date'] = stocklist[30][:8]               # ʱ��
    stockdict['block'] = False if stockdict['start'] else True #��Ʊ�Ƿ�ͣ��
    stockdict['circulation_market_value '] = float(stocklist[44])
    stockdict['total_value '] = float(stocklist[45])
    stockdict['high_limit'] = float(stocklist[47])
    stockdict['low_limit'] = float(stocklist[48])
    return stockdict

#��ȡ���й�Ʊ�б�
def get_stock_list():
    #url = 'http://www.shdjt.com/js/lib/astock.js'
    url = 'http://www.ctxalgo.com/api/stocks'
    res = urllib2.urlopen(url).read()
    #print res
    id_dic= json.loads(res)
    return id_dic


#ȥ��ͣ�Ƶ�
def get_basic_list():
    id_dic = get_stock_list()

    selected_dic = {}
    for key in id_dic:
        time.sleep(3)
        res = get_stockid_real_time(key)
        if res['block']:  #ͣ��
            continue

        if res['circulation_market_value '] > 100:
            continue

        if res['pe'] >= 100:
            continue

        if res['low']  > 30:
            continue

        if res['change_rate'] < 1:
            continue

        res['name'] = id_dic[key].decode("unicode_escape")

        print res


if __name__ == '__main__':
    #id_dic = get_stock_list()
    get_basic_list()
    #for key in id_dic:
    #    print key, id_dic[key]
    #get_stockid_real_time('sz002859')
    #get_stockid_detail('2017-10-13', 'sz002859')

