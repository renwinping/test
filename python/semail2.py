#coding=gbk
#!/usr/bin/python

import smtplib
from email.mime.text import MIMEText
mailto_list=["zhangming025251@gmail.com"]
mail_host="smtp.gmail.com"  #���÷�����
mail_user="zhangming025251"    #�û���
mail_pass="scat952pat469"   #����
mail_postfix="gmail.com"  #��a����ĺ�׺

def send_mail(to_list,sub,content):  #to_list���ռ��ˣ�sub�����⣻content���ʼ�����
    me="zhangming025251"+"<"+mail_user+"@"+mail_postfix+">"   #�����hello�����������ã��յ��ź󣬽�����������ʾ
    msg = MIMEText(content,_subtype='html',_charset='gb2312')    #����һ��ʵ������������Ϊhtml��ʽ�ʼ�
    msg['Subject'] = 'hello world'    #��������
    msg['From'] = me
    msg['To'] = ";".join(to_list)
    try:
        s = smtplib.SMTP(mail_host, port=25, timeout=60)
        #s.connect(mail_host, 25)  #����smtp������
        #s.ehlo()
        print 11111
        s.starttls()
        print 333333
        #s.ehlo()
        s.login("zhangming025251","scat952pat469")  #��½������
        print 222
        s.sendmail(me, to_list, msg.as_string())  #�����ʼ�
        s.close()
        return True
    except Exception, e:
        print str(e)
        return False
if __name__ == '__main__':
    if send_mail(mailto_list,mail_user,"<a href='http://www.cnblogs.com/xiaowuyi'>����������</a>"):
        print "���ͳɹ�"
    else:
        print "����ʧ��"