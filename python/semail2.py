#coding=gbk
#!/usr/bin/python

import smtplib
from email.mime.text import MIMEText
mailto_list=["zhangming025251@gmail.com"]
mail_host="smtp.126.com"  #���÷�����
mail_user="chenfeng025251"    #�û���
mail_pass="scat952pat469"   #����
mail_postfix="126.com"  #��a����ĺ�׺

def send_mail(to_list,sub,content):  #to_list���ռ��ˣ�sub�����⣻content���ʼ�����
    me="chen"+"<"+mail_user+"@"+mail_postfix+">"   #�����hello�����������ã��յ��ź󣬽�����������ʾ
    msg = MIMEText(content,_subtype='html',_charset='gb2312')    #����һ��ʵ������������Ϊhtml��ʽ�ʼ�
    msg['Subject'] = 'hello world'    #��������
    msg['From'] = me
    msg['To'] = ";".join(to_list)
    try:
        s = smtplib.SMTP(mail_host, port=25, timeout=60)
        #s.connect(mail_host, 25)  #����smtp������
        #s.ehlo()
        #print 11111
        s.starttls()
        #print 333333
        #s.ehlo()
        s.login("chenfeng025251","scat952pat469")  #��½������
        #print 222
        s.sendmail(me, to_list, msg.as_string())  #�����ʼ�
        s.close()
        return True
    except Exception, e:
        print str(e)
        return False
if __name__ == '__main__':
    #if send_mail(mailto_list,mail_user,"<a href='http://www.cnblogs.com/xiaowuyi'>����������</a>"):
    if send_mail(mailto_list,mail_user,'''<div class="nH aHU"><div class="nH hx"><div class="nH"><div tabindex="-1" role="menu" class="b7 J-M" aria-haspopup="true" style="-webkit-user-select: none; display: none;"></div></div><div class="nH"><div class="nH"></div></div><div class="nH" role="list"><div class="h7  ie nH oy8Mbf" role="listitem" tabindex="-1"><div class="Bk"><div class="G3 G2"><div><div id=":la"><div class="adn ads" style="display:"><div class="aju"><div class="aCi"><div class="aFg" style="display: none;"></div><img id=":0_2-e" name=":0" src="//ssl.gstatic.com/ui/v1/icons/mail/profile_mask2.png" class="ajn" style="background-color: #cccccc" jid="email@engage.redhat.com" data-name="Red Hat" aria-hidden="true"></div></div><div class="gs"><div class="gE iv gt"><table cellpadding="0" class="cf gJ"><tbody><tr class="acZ"><td class="gF gK"><table cellpadding="0" class="cf ix"><tbody><tr><td><h3 class="iw"><span email="email@engage.redhat.com" name="Red Hat" class="gD">Red Hat</span> <span class="go"><span aria-hidden="true">&lt;</span>email@engage.redhat.com<span aria-hidden="true">&gt;</span></span> <span class="Ca" idlink="" tabindex="0">ȡ������</span></h3></td></tr></tbody></table></td><td class="gH"><div class="gK"><span></span><span id=":kq" class="g3" title="2016��5��4�� ����10:08" alt="2016��5��4�� ����10:08">5��4��</span><div class="zd" aria-label="�Ѽ��Ǳ�" tabindex="0" role="checkbox" aria-checked="false" style="outline:0"><span class="T-KT" onselectstart="return false;"><img class="f T-KT-JX" src="images/cleardot.gif" alt=""></span></div></div></td><td class="gH"></td><td class="gH acX" rowspan="2"><div class="T-I J-J5-Ji T-I-Js-IF aaq T-I-ax7 L3" role="button" tabindex="0" data-tooltip="�ظ�" aria-label="�ظ�" style="-webkit-user-select: none;"><img class="hB T-I-J3" role="button" src="images/cleardot.gif" alt=""></div><div id=":l3" class="T-I J-J5-Ji T-I-Js-Gs aap T-I-awG T-I-ax7 L3" role="button" tabindex="0" aria-expanded="false" aria-haspopup="true" data-tooltip="�������" aria-label="�������" style="-webkit-user-select: none;"><img class="hA T-I-J3" role="menu" src="images/cleardot.gif" alt=""></div></td></tr><tr class="acZ xD"><td colspan="3"><table cellpadding="0" class="cf adz"><tbody><tr><td class="ady"><div class="iw ajw"><span class="bat" role="img" data-tooltip="redhat.com δ�Դ��ʼ����м���" aria-label="redhat.com δ�Դ��ʼ����м���"></span><span class="hb">������ <span dir="ltr" email="zhangming025251@gmail.com" name="��" class="g2">��</span> </span></div><div aria-haspopup="true" class="ajy"><img class="ajz" id=":l4" role="button" src="images/cleardot.gif" alt="" data-tooltip="��ʾ��ϸ��Ϣ" aria-label="��ʾ��ϸ��Ϣ"></div></td></tr></tbody></table></td></tr></tbody></table></div><div class="qQVYZb"></div><div class="utdU2e"></div><div class="tx78Ic"></div><div class="aHl"></div><div id=":l5" tabindex="-1"></div><div id=":l8" class="ii gt adP adO"><div id=":l9" class="a3s aXjCH m1547986a2fbf2cbf"><u></u>







<div style="text-align:center;padding:0;margin:0">

<table align="center" border="0" cellpadding="0" cellspacing="0" width="769">
	<tbody>
		<tr>
			<td align="center" style="font-family:simsun,Helvetica,sans-serif;font-size:12px;color:#cc0000"><a href="http://app.engage.redhat.com/e/es?s=1795&amp;e=847875&amp;elqTrackId=f1d21069abe6472692e1a06e356cbf9e&amp;elq=e6d1559468b842f1be8104b7909ec13a&amp;elqaid=26659&amp;elqat=1" style="color:#cc0000!important;text-decoration:none!important" target="_blank" data-saferedirecturl="https://www.google.com/url?hl=zh-CN&amp;q=http://app.engage.redhat.com/e/es?s%3D1795%26e%3D847875%26elqTrackId%3Df1d21069abe6472692e1a06e356cbf9e%26elq%3De6d1559468b842f1be8104b7909ec13a%26elqaid%3D26659%26elqat%3D1&amp;source=gmail&amp;ust=1463648584447000&amp;usg=AFQjCNHlQlYyKkL5mXbt8_v0T4nNnE0X1A">��ñ��������������޹�˾</a><br>
			&nbsp;</td>
		</tr>
	</tbody>
</table>





<div style="font-family:Overpass,Arial,Helvetica,sans-serif;width:642px;margin-left:auto;margin-right:auto">
  <table width="642" border="0" align="center" cellpadding="0" cellspacing="0" style="background-color:#ffffff;border:1px solid #cccccc">
    <tbody>
      <tr>
        <td width="640" align="left" valign="top" bgcolor="#FFFFFF">

          <table width="640" cellpadding="0" cellspacing="0" border="0">
            <tbody>
              <tr>
                <td width="640" align="left" valign="top"><table width="640" cellpadding="0" cellspacing="0" border="0" style="width:640px;max-width:640px;min-width:640px">
                    <tbody>
                      <tr>
                        <td width="640" height="415" style="line-height:319px" align="left" valign="top"><a href="http://app.engage.redhat.com/e/er?s=1795&amp;lid=37684&amp;elqTrackId=ecef6fef756144178438e61523a2a67a&amp;elq=e6d1559468b842f1be8104b7909ec13a&amp;elqaid=26659&amp;elqat=1" target="_blank" data-saferedirecturl="https://www.google.com/url?hl=zh-CN&amp;q=http://app.engage.redhat.com/e/er?s%3D1795%26lid%3D37684%26elqTrackId%3Decef6fef756144178438e61523a2a67a%26elq%3De6d1559468b842f1be8104b7909ec13a%26elqaid%3D26659%26elqat%3D1&amp;source=gmail&amp;ust=1463648584447000&amp;usg=AFQjCNGvtIoTB3YPO7GIoLr6Wzcqql-PJw"><img src="https://ci6.googleusercontent.com/proxy/qs5LRrA0pNB25jYH48yT9WSmiWKsae5MZuEpM_iYuxqkLXoCAgedMj2yIu6IibXfXXv2z1iNZPzpBpiaNK-z5A8Ofd60MW2VDlxg6FaqC7L6cQVdnsE_R99ut6rSy0MCcO5ciEUrsaUUWPf0-4bnFlTPExfkWr3JjClUY7v-pTkMTm4=s0-d-e1-ft#http://images.engage.redhat.com/EloquaImages/clients/RedHat/%7b55c87f43-7f4f-4e33-b033-2cdf2aab0356%7d_kv.jpg" width="640" height="415" border="0" alt="�����ñ������սӮȡʤ����" title="�����ñ������սӮȡʤ����" style="display:block;width:640x;min-width:640px" class="CToWUd"></a></td>
                      </tr>
                    </tbody>
                  </table>
                  <table cellpadding="0" cellspacing="0" border="0" style="width:0;height:0;overflow:hidden;line-height:0;font-size:0;margin:0;padding:0;max-height:0">
                    <tbody>
                      <tr>
                        <td valign="top" align="left" style="width:0;height:0;overflow:hidden;line-height:0;font-size:0;margin:0;padding:0;max-height:0"><a href="http://app.engage.redhat.com/e/er?s=1795&amp;lid=37684&amp;elqTrackId=5c9894bb40ec4aa4bb533baddb1a5f1f&amp;elq=e6d1559468b842f1be8104b7909ec13a&amp;elqaid=26659&amp;elqat=1" target="_blank" data-saferedirecturl="https://www.google.com/url?hl=zh-CN&amp;q=http://app.engage.redhat.com/e/er?s%3D1795%26lid%3D37684%26elqTrackId%3D5c9894bb40ec4aa4bb533baddb1a5f1f%26elq%3De6d1559468b842f1be8104b7909ec13a%26elqaid%3D26659%26elqat%3D1&amp;source=gmail&amp;ust=1463648584447000&amp;usg=AFQjCNG1h1RGgBrWlKPHRH_TOup5SRIKig"><img src="https://ci6.googleusercontent.com/proxy/NVCSI-2IyqIZukdC7BN0O_TkbybOuRPp9WYbVfOML0eV6KjOyzq9yQ39KQsOkmhoFZ1rLcF5o2XqKl5K_mbPTM-DShVPJDvbctxcd4j1rAM5ABo15sfuR23EO0zWNd1fm_fQ5jMyuoKXvWecG8ZJQzJBhW_P8UP9367qu8SgBIYTj2vsgAiVrvex=s0-d-e1-ft#http://images.engage.redhat.com/EloquaImages/clients/RedHat/%7b969f2e6e-3e20-4d9e-8bf0-ceb10be1ba7b%7d_kv-mobile.jpg" width="0" height="0" border="0" alt="�����ñ������սӮȡʤ����" title="�����ñ������սӮȡʤ����" class="CToWUd"></a></td>
                      </tr>
                    </tbody>
                  </table>
                  <table width="640" cellpadding="0" cellspacing="0" border="0" style="table-layout:fixed">
                    <tbody>
                      <tr>
                        <td align="left" valign="top" width="640" height="20"><img src="https://ci3.googleusercontent.com/proxy/PmiJRizlbfNJbygMXAAIf_YCMx3yywsuZRR2hzmJMypwofBNFOHvAf-ws8_2NTUEkheZcUBJztE7XPIPzzkgUGIIIzWj3Tn1sLh6-p8BXOlMO_nf4tZ5z1jFvadH6ARz5rxMoDix1SCiwWX2ZRtpm5kHA8Io9JlbAGEekhIT0btv0A=s0-d-e1-ft#http://images.engage.redhat.com/EloquaImages/clients/RedHat/%7b217d48d9-b987-444f-a169-e51ab03a95a1%7d_s.gif" width="640" height="20" border="0" alt="" style="display:block" class="CToWUd"></td>
                      </tr>
                    </tbody>
                  </table>




                  <table width="640" cellpadding="0" cellspacing="0" border="0">
                    <tbody>
                      <tr>
                        <td width="25" height="10" valign="top" align="left"><img src="https://ci3.googleusercontent.com/proxy/PmiJRizlbfNJbygMXAAIf_YCMx3yywsuZRR2hzmJMypwofBNFOHvAf-ws8_2NTUEkheZcUBJztE7XPIPzzkgUGIIIzWj3Tn1sLh6-p8BXOlMO_nf4tZ5z1jFvadH6ARz5rxMoDix1SCiwWX2ZRtpm5kHA8Io9JlbAGEekhIT0btv0A=s0-d-e1-ft#http://images.engage.redhat.com/EloquaImages/clients/RedHat/%7b217d48d9-b987-444f-a169-e51ab03a95a1%7d_s.gif" width="25" height="10" border="0" alt="" style="display:block" class="CToWUd"></td>
                        <td width="590" align="left" valign="top" style="width:590px;font-family:Overpass,Arial,Helvetica,sans-serif;font-size:15px;line-height:18px;color:#333333"><strong>��90% �Ƹ� 500 ǿ��ҵ���еĺ�ñϵͳ��������ñ��˾��������</strong> ��ȷ���Ǵ���<br>
                          <br>
                          ��֪�����������˽������κ��йغ�ñ��˾����Ϣ��<wbr>����������ԣ���������֪ʶ��֤���Լ��� IT ������ͬһ�㡣<br>
                          <br>
                          ����õ��������ķ�������ɽ���ݮ���������У���Ϊ���ֻ�� 20 ���������ץ��ʱ���ж��ɡ�ף�����ˣ�</td>
                        <td width="25" height="10" valign="top" align="left"><img src="https://ci3.googleusercontent.com/proxy/PmiJRizlbfNJbygMXAAIf_YCMx3yywsuZRR2hzmJMypwofBNFOHvAf-ws8_2NTUEkheZcUBJztE7XPIPzzkgUGIIIzWj3Tn1sLh6-p8BXOlMO_nf4tZ5z1jFvadH6ARz5rxMoDix1SCiwWX2ZRtpm5kHA8Io9JlbAGEekhIT0btv0A=s0-d-e1-ft#http://images.engage.redhat.com/EloquaImages/clients/RedHat/%7b217d48d9-b987-444f-a169-e51ab03a95a1%7d_s.gif" width="25" height="10" border="0" alt="" style="display:block" class="CToWUd"></td>
                      </tr>
                    </tbody>
                  </table>
                  <table width="640" cellpadding="0" cellspacing="0" border="0" style="table-layout:fixed">
                    <tbody>
                      <tr>
                        <td align="left" valign="top" width="640" height="30" style="line-height:30px"><img src="https://ci3.googleusercontent.com/proxy/PmiJRizlbfNJbygMXAAIf_YCMx3yywsuZRR2hzmJMypwofBNFOHvAf-ws8_2NTUEkheZcUBJztE7XPIPzzkgUGIIIzWj3Tn1sLh6-p8BXOlMO_nf4tZ5z1jFvadH6ARz5rxMoDix1SCiwWX2ZRtpm5kHA8Io9JlbAGEekhIT0btv0A=s0-d-e1-ft#http://images.engage.redhat.com/EloquaImages/clients/RedHat/%7b217d48d9-b987-444f-a169-e51ab03a95a1%7d_s.gif" width="640" height="30" border="0" alt="" style="display:block" class="CToWUd"></td>
                      </tr>
                    </tbody>
                  </table>
                  <table width="640" cellpadding="0" cellspacing="0" border="0">
                    <tbody>
                      <tr>
                        <td width="25" height="10" valign="top" align="left"><img src="https://ci3.googleusercontent.com/proxy/PmiJRizlbfNJbygMXAAIf_YCMx3yywsuZRR2hzmJMypwofBNFOHvAf-ws8_2NTUEkheZcUBJztE7XPIPzzkgUGIIIzWj3Tn1sLh6-p8BXOlMO_nf4tZ5z1jFvadH6ARz5rxMoDix1SCiwWX2ZRtpm5kHA8Io9JlbAGEekhIT0btv0A=s0-d-e1-ft#http://images.engage.redhat.com/EloquaImages/clients/RedHat/%7b217d48d9-b987-444f-a169-e51ab03a95a1%7d_s.gif" width="25" height="10" border="0" alt="" style="display:block" class="CToWUd"></td>
                        <td width="590" align="left" valign="top" style="width:590px;font-family:Overpass,Arial,Helvetica,sans-serif;font-size:12px;line-height:15px"><a href="http://app.engage.redhat.com/e/er?s=1795&amp;lid=37684&amp;elqTrackId=10e39477a1344f9ab12061d43e311ef4&amp;elq=e6d1559468b842f1be8104b7909ec13a&amp;elqaid=26659&amp;elqat=1" target="_blank" data-saferedirecturl="https://www.google.com/url?hl=zh-CN&amp;q=http://app.engage.redhat.com/e/er?s%3D1795%26lid%3D37684%26elqTrackId%3D10e39477a1344f9ab12061d43e311ef4%26elq%3De6d1559468b842f1be8104b7909ec13a%26elqaid%3D26659%26elqat%3D1&amp;source=gmail&amp;ust=1463648584447000&amp;usg=AFQjCNEZknKlz07puns96PxqQRKzGc2dsA"><img src="https://ci4.googleusercontent.com/proxy/H6yyED191lse2sOascH-MPIHf4GacZHO44zRYE1mzA1noAwMFI8RWQIS3r2l95_ajBgA4IUZ6epkrQM5svFYOAPugPhAoOfhcK73AvR3_AOVq8Joue9U4VuRs6r90NEpFkrmOV42K0Q2Xdm_miuthVFFcTCxRN8piCV3umCh7idx0K2DMemiclUFsNPT_A=s0-d-e1-ft#http://images.engage.redhat.com/EloquaImages/clients/RedHat/%7bd140c840-427c-499b-b5ea-119ea7d185a9%7d_btn-bringiton.jpg" width="157" height="34" border="0" title="��ʼ�ж���" alt="��ʼ�ж���" style="display:inline-block" class="CToWUd"></a></td>
                        <td width="25" height="10" valign="top" align="left"><img src="https://ci3.googleusercontent.com/proxy/PmiJRizlbfNJbygMXAAIf_YCMx3yywsuZRR2hzmJMypwofBNFOHvAf-ws8_2NTUEkheZcUBJztE7XPIPzzkgUGIIIzWj3Tn1sLh6-p8BXOlMO_nf4tZ5z1jFvadH6ARz5rxMoDix1SCiwWX2ZRtpm5kHA8Io9JlbAGEekhIT0btv0A=s0-d-e1-ft#http://images.engage.redhat.com/EloquaImages/clients/RedHat/%7b217d48d9-b987-444f-a169-e51ab03a95a1%7d_s.gif" width="25" height="10" border="0" alt="" style="display:block" class="CToWUd"></td>
                      </tr>
                    </tbody>
                  </table>
                  <table width="640" cellpadding="0" cellspacing="0" border="0" style="table-layout:fixed">
                    <tbody>
                      <tr>
                        <td align="left" valign="top" width="640" height="30" style="line-height:30px"><img src="https://ci3.googleusercontent.com/proxy/PmiJRizlbfNJbygMXAAIf_YCMx3yywsuZRR2hzmJMypwofBNFOHvAf-ws8_2NTUEkheZcUBJztE7XPIPzzkgUGIIIzWj3Tn1sLh6-p8BXOlMO_nf4tZ5z1jFvadH6ARz5rxMoDix1SCiwWX2ZRtpm5kHA8Io9JlbAGEekhIT0btv0A=s0-d-e1-ft#http://images.engage.redhat.com/EloquaImages/clients/RedHat/%7b217d48d9-b987-444f-a169-e51ab03a95a1%7d_s.gif" width="640" height="30" border="0" alt="" style="display:block" class="CToWUd"></td>
                      </tr>
                    </tbody>
                  </table>
                  <table width="640" cellpadding="0" cellspacing="0" border="0">
                    <tbody>
                      <tr>
                        <td width="25" height="10" valign="top" align="left"><img src="https://ci3.googleusercontent.com/proxy/PmiJRizlbfNJbygMXAAIf_YCMx3yywsuZRR2hzmJMypwofBNFOHvAf-ws8_2NTUEkheZcUBJztE7XPIPzzkgUGIIIzWj3Tn1sLh6-p8BXOlMO_nf4tZ5z1jFvadH6ARz5rxMoDix1SCiwWX2ZRtpm5kHA8Io9JlbAGEekhIT0btv0A=s0-d-e1-ft#http://images.engage.redhat.com/EloquaImages/clients/RedHat/%7b217d48d9-b987-444f-a169-e51ab03a95a1%7d_s.gif" width="25" height="10" border="0" alt="" style="display:block" class="CToWUd"></td>
                        <td width="590" align="left" valign="top" style="width:590px;font-family:Overpass,Arial,Helvetica,sans-serif;font-size:12px;line-height:15px;color:#333333"><a href="http://app.engage.redhat.com/e/er?s=1795&amp;lid=36882&amp;elqTrackId=417fb7bbf27448f9baef521b7a25142b&amp;elq=e6d1559468b842f1be8104b7909ec13a&amp;elqaid=26659&amp;elqat=1" style="font-family:Overpass,Arial,Helvetica,sans-serif;font-size:12px;line-height:15px;color:#666666;text-decoration:underline" target="_blank" data-saferedirecturl="https://www.google.com/url?hl=zh-CN&amp;q=http://app.engage.redhat.com/e/er?s%3D1795%26lid%3D36882%26elqTrackId%3D417fb7bbf27448f9baef521b7a25142b%26elq%3De6d1559468b842f1be8104b7909ec13a%26elqaid%3D26659%26elqat%3D1&amp;source=gmail&amp;ust=1463648584447000&amp;usg=AFQjCNEd47gZKa_Fg_SEa93NS3WPtgniSQ"><font style="font-family:Overpass,Arial,Helvetica,sans-serif;font-size:12px;line-height:15px;color:#666666;text-decoration:underline">����ѭ�������������</font></a></td>
                        <td width="25" height="10" valign="top" align="left"><img src="https://ci3.googleusercontent.com/proxy/PmiJRizlbfNJbygMXAAIf_YCMx3yywsuZRR2hzmJMypwofBNFOHvAf-ws8_2NTUEkheZcUBJztE7XPIPzzkgUGIIIzWj3Tn1sLh6-p8BXOlMO_nf4tZ5z1jFvadH6ARz5rxMoDix1SCiwWX2ZRtpm5kHA8Io9JlbAGEekhIT0btv0A=s0-d-e1-ft#http://images.engage.redhat.com/EloquaImages/clients/RedHat/%7b217d48d9-b987-444f-a169-e51ab03a95a1%7d_s.gif" width="25" height="10" border="0" alt="" style="display:block" class="CToWUd"></td>
                      </tr>
                    </tbody>
                  </table>
                  <table width="640" cellpadding="0" cellspacing="0" border="0" style="table-layout:fixed">
                    <tbody>
                      <tr>
                        <td align="left" valign="top" width="640" height="40" style="line-height:40px;border-bottom:1px solid #cccccc"><img src="https://ci3.googleusercontent.com/proxy/PmiJRizlbfNJbygMXAAIf_YCMx3yywsuZRR2hzmJMypwofBNFOHvAf-ws8_2NTUEkheZcUBJztE7XPIPzzkgUGIIIzWj3Tn1sLh6-p8BXOlMO_nf4tZ5z1jFvadH6ARz5rxMoDix1SCiwWX2ZRtpm5kHA8Io9JlbAGEekhIT0btv0A=s0-d-e1-ft#http://images.engage.redhat.com/EloquaImages/clients/RedHat/%7b217d48d9-b987-444f-a169-e51ab03a95a1%7d_s.gif" width="640" height="40" border="0" alt="" style="display:block" class="CToWUd"></td>
                      </tr>
                    </tbody>
                  </table></td>
              </tr>
            </tbody>
          </table>






          <table width="640" cellpadding="0" cellspacing="0" border="0" style="table-layout:fixed" bgcolor="#FFFFFF">
            <tbody>
              <tr>
                <td align="left" valign="top" width="640" height="30"><img src="https://ci3.googleusercontent.com/proxy/PmiJRizlbfNJbygMXAAIf_YCMx3yywsuZRR2hzmJMypwofBNFOHvAf-ws8_2NTUEkheZcUBJztE7XPIPzzkgUGIIIzWj3Tn1sLh6-p8BXOlMO_nf4tZ5z1jFvadH6ARz5rxMoDix1SCiwWX2ZRtpm5kHA8Io9JlbAGEekhIT0btv0A=s0-d-e1-ft#http://images.engage.redhat.com/EloquaImages/clients/RedHat/%7b217d48d9-b987-444f-a169-e51ab03a95a1%7d_s.gif" width="640" height="30" border="0" alt="" style="display:block;line-height:30px" class="CToWUd"></td>
              </tr>
            </tbody>
          </table>
          <table width="640" cellpadding="0" cellspacing="0" border="0" bgcolor="#FFFFFF">
            <tbody>
              <tr>
                <td width="25" height="33" valign="top" align="left" style="line-height:33px"><img src="https://ci3.googleusercontent.com/proxy/PmiJRizlbfNJbygMXAAIf_YCMx3yywsuZRR2hzmJMypwofBNFOHvAf-ws8_2NTUEkheZcUBJztE7XPIPzzkgUGIIIzWj3Tn1sLh6-p8BXOlMO_nf4tZ5z1jFvadH6ARz5rxMoDix1SCiwWX2ZRtpm5kHA8Io9JlbAGEekhIT0btv0A=s0-d-e1-ft#http://images.engage.redhat.com/EloquaImages/clients/RedHat/%7b217d48d9-b987-444f-a169-e51ab03a95a1%7d_s.gif" width="25" height="33" border="0" alt="" style="display:block" class="CToWUd"></td>
                <td width="590" align="left" valign="top" style="width:590px;font-family:Overpass,Arial,Helvetica,sans-serif;font-size:12px;line-height:15px"><table width="70" border="0" cellspacing="0" cellpadding="0" align="left" style="height:33px;table-layout:fixed;font-family:Overpass,Arial,Helvetica,sans-serif;font-size:11px;line-height:17px;color:#333333">
                    <tbody>
                      <tr>
                        <td width="70" height="33" align="left" valign="middle" style="font-family:Overpass,Arial,Helvetica,sans-serif;font-size:14px;color:#333333;line-height:17px">��ϵ����</td>
                      </tr>
                    </tbody>
                  </table>
                  <table width="102" border="0" cellspacing="0" cellpadding="0" style="table-layout:fixed">
                    <tbody>
                      <tr>
                        <td align="center" valign="top" width="90"><table width="102" border="0" cellspacing="0" cellpadding="0" style="table-layout:fixed;font-family:Overpass,Arial,Helvetica,sans-serif;font-size:11px;line-height:normal">
                            <tbody>
                              <tr>
                                <td align="left" valign="top" width="12"><img src="https://ci3.googleusercontent.com/proxy/PmiJRizlbfNJbygMXAAIf_YCMx3yywsuZRR2hzmJMypwofBNFOHvAf-ws8_2NTUEkheZcUBJztE7XPIPzzkgUGIIIzWj3Tn1sLh6-p8BXOlMO_nf4tZ5z1jFvadH6ARz5rxMoDix1SCiwWX2ZRtpm5kHA8Io9JlbAGEekhIT0btv0A=s0-d-e1-ft#http://images.engage.redhat.com/EloquaImages/clients/RedHat/%7b217d48d9-b987-444f-a169-e51ab03a95a1%7d_s.gif" width="12" height="33" border="0" alt="" style="display:block" class="CToWUd"></td>
                                <td align="left" valign="top" width="33"><a href="http://app.engage.redhat.com/e/er?s=1795&amp;lid=37685&amp;elqTrackId=44f5f28dcfc142acbe53c40e1e005ca8&amp;elq=e6d1559468b842f1be8104b7909ec13a&amp;elqaid=26659&amp;elqat=1" target="_blank" data-saferedirecturl="https://www.google.com/url?hl=zh-CN&amp;q=http://app.engage.redhat.com/e/er?s%3D1795%26lid%3D37685%26elqTrackId%3D44f5f28dcfc142acbe53c40e1e005ca8%26elq%3De6d1559468b842f1be8104b7909ec13a%26elqaid%3D26659%26elqat%3D1&amp;source=gmail&amp;ust=1463648584447000&amp;usg=AFQjCNF1Ct2jkL7Z1oqgq3Vtd6DYBnsBoA"><img src="https://ci4.googleusercontent.com/proxy/8YYiaELV85FiGb5c2gfkb-J7YK_8pHdr9QiKiTWJIYSGwBPHTWvVR6aEOMB1ATOuN5ThPagApSG3oa8bne9RXwOOVqsa5leO-iESDUiP91qO9CtLH7C4lD_Pg5U8mo3ItOkm5i5EuTjfc_eIniqsyd-jzAkiv5sFvpIsSwuOw60eBhd6Lc9oHaYIiVSM=s0-d-e1-ft#http://images.engage.redhat.com/EloquaImages/clients/RedHat/%7b0110ca28-3ed9-4331-b9ce-bcb48daf2802%7d_ico_linkedin.jpg" width="33" height="33" border="0" alt="Linkedin" title="Linkedin" style="display:block" class="CToWUd"></a></td>
                                <td align="left" valign="top" width="12"><img src="https://ci3.googleusercontent.com/proxy/PmiJRizlbfNJbygMXAAIf_YCMx3yywsuZRR2hzmJMypwofBNFOHvAf-ws8_2NTUEkheZcUBJztE7XPIPzzkgUGIIIzWj3Tn1sLh6-p8BXOlMO_nf4tZ5z1jFvadH6ARz5rxMoDix1SCiwWX2ZRtpm5kHA8Io9JlbAGEekhIT0btv0A=s0-d-e1-ft#http://images.engage.redhat.com/EloquaImages/clients/RedHat/%7b217d48d9-b987-444f-a169-e51ab03a95a1%7d_s.gif" width="12" height="33" border="0" alt="" style="display:block" class="CToWUd"></td>
                                <td align="left" valign="top" width="33"><a href="http://app.engage.redhat.com/e/er?s=1795&amp;lid=30446&amp;elqTrackId=c1d76864e8af405f879f947c8b9c4292&amp;elq=e6d1559468b842f1be8104b7909ec13a&amp;elqaid=26659&amp;elqat=1" target="_blank" data-saferedirecturl="https://www.google.com/url?hl=zh-CN&amp;q=http://app.engage.redhat.com/e/er?s%3D1795%26lid%3D30446%26elqTrackId%3Dc1d76864e8af405f879f947c8b9c4292%26elq%3De6d1559468b842f1be8104b7909ec13a%26elqaid%3D26659%26elqat%3D1&amp;source=gmail&amp;ust=1463648584447000&amp;usg=AFQjCNEHW9uqDHq6XfRPEkso6sv0MhuDNw"><img src="https://ci3.googleusercontent.com/proxy/8xWwsA0YFxqsq03beH0GfM3Ld9D3PSHIfFQYsFHDr2GJjyqWU_dt5mKmCs1zYFiQMYTupkxreI28ylRSMZsZPcEcISil4wxqoCqNjXYmGa7xMCPQpy9DqVMxPA20tA19HMmRQ0iLeeraTGtWhE4qHDmIOOCgQV1pHLgo9RIZ9YS5ajsIn15UivmP044=s0-d-e1-ft#http://images.engage.redhat.com/EloquaImages/clients/RedHat/%7b86505874-ba73-40f8-9d5e-e99cbe8b660f%7d_ico_twitter.jpg" width="33" height="33" border="0" alt="Twitter" title="Twitter" style="display:block" class="CToWUd"></a></td>
                                <td align="left" valign="top" width="12"><img src="https://ci3.googleusercontent.com/proxy/PmiJRizlbfNJbygMXAAIf_YCMx3yywsuZRR2hzmJMypwofBNFOHvAf-ws8_2NTUEkheZcUBJztE7XPIPzzkgUGIIIzWj3Tn1sLh6-p8BXOlMO_nf4tZ5z1jFvadH6ARz5rxMoDix1SCiwWX2ZRtpm5kHA8Io9JlbAGEekhIT0btv0A=s0-d-e1-ft#http://images.engage.redhat.com/EloquaImages/clients/RedHat/%7b217d48d9-b987-444f-a169-e51ab03a95a1%7d_s.gif" width="12" height="33" border="0" alt="" style="display:block" class="CToWUd"></td>
                              </tr>
                            </tbody>
                          </table></td>
                      </tr>
                    </tbody>
                  </table></td>
                <td width="25" height="33" valign="top" align="left" style="line-height:33px"><img src="https://ci3.googleusercontent.com/proxy/PmiJRizlbfNJbygMXAAIf_YCMx3yywsuZRR2hzmJMypwofBNFOHvAf-ws8_2NTUEkheZcUBJztE7XPIPzzkgUGIIIzWj3Tn1sLh6-p8BXOlMO_nf4tZ5z1jFvadH6ARz5rxMoDix1SCiwWX2ZRtpm5kHA8Io9JlbAGEekhIT0btv0A=s0-d-e1-ft#http://images.engage.redhat.com/EloquaImages/clients/RedHat/%7b217d48d9-b987-444f-a169-e51ab03a95a1%7d_s.gif" width="25" height="33" border="0" alt="" style="display:block" class="CToWUd"></td>
              </tr>
              <tr>
                <td width="25" height="30" valign="top" align="left" style="line-height:30px"><img src="https://ci3.googleusercontent.com/proxy/PmiJRizlbfNJbygMXAAIf_YCMx3yywsuZRR2hzmJMypwofBNFOHvAf-ws8_2NTUEkheZcUBJztE7XPIPzzkgUGIIIzWj3Tn1sLh6-p8BXOlMO_nf4tZ5z1jFvadH6ARz5rxMoDix1SCiwWX2ZRtpm5kHA8Io9JlbAGEekhIT0btv0A=s0-d-e1-ft#http://images.engage.redhat.com/EloquaImages/clients/RedHat/%7b217d48d9-b987-444f-a169-e51ab03a95a1%7d_s.gif" width="25" height="30" border="0" alt="" style="display:block" class="CToWUd"></td>
                <td width="590" height="30" align="left" valign="top" style="line-height:30px"><img src="https://ci3.googleusercontent.com/proxy/PmiJRizlbfNJbygMXAAIf_YCMx3yywsuZRR2hzmJMypwofBNFOHvAf-ws8_2NTUEkheZcUBJztE7XPIPzzkgUGIIIzWj3Tn1sLh6-p8BXOlMO_nf4tZ5z1jFvadH6ARz5rxMoDix1SCiwWX2ZRtpm5kHA8Io9JlbAGEekhIT0btv0A=s0-d-e1-ft#http://images.engage.redhat.com/EloquaImages/clients/RedHat/%7b217d48d9-b987-444f-a169-e51ab03a95a1%7d_s.gif" width="590" height="30" border="0" alt="" style="display:block" class="CToWUd"></td>
                <td width="25" height="30" valign="top" align="left" style="line-height:30px"><img src="https://ci3.googleusercontent.com/proxy/PmiJRizlbfNJbygMXAAIf_YCMx3yywsuZRR2hzmJMypwofBNFOHvAf-ws8_2NTUEkheZcUBJztE7XPIPzzkgUGIIIzWj3Tn1sLh6-p8BXOlMO_nf4tZ5z1jFvadH6ARz5rxMoDix1SCiwWX2ZRtpm5kHA8Io9JlbAGEekhIT0btv0A=s0-d-e1-ft#http://images.engage.redhat.com/EloquaImages/clients/RedHat/%7b217d48d9-b987-444f-a169-e51ab03a95a1%7d_s.gif" width="25" height="30" border="0" alt="" style="display:block" class="CToWUd"></td>
              </tr>
              <tr>
                <td width="25" height="10" valign="top" align="left"><img src="https://ci3.googleusercontent.com/proxy/PmiJRizlbfNJbygMXAAIf_YCMx3yywsuZRR2hzmJMypwofBNFOHvAf-ws8_2NTUEkheZcUBJztE7XPIPzzkgUGIIIzWj3Tn1sLh6-p8BXOlMO_nf4tZ5z1jFvadH6ARz5rxMoDix1SCiwWX2ZRtpm5kHA8Io9JlbAGEekhIT0btv0A=s0-d-e1-ft#http://images.engage.redhat.com/EloquaImages/clients/RedHat/%7b217d48d9-b987-444f-a169-e51ab03a95a1%7d_s.gif" width="25" height="10" border="0" alt="" style="display:block" class="CToWUd"></td>
                <td width="590" align="left" valign="top" style="width:590px;font-family:Overpass,Arial,Helvetica,sans-serif;font-size:12px;line-height:15px;color:#666666"><a href="http://app.engage.redhat.com/e/er?s=1795&amp;lid=18901&amp;elqTrackId=09a0bde0d86646b7af860bbe3dbde41b&amp;elq=e6d1559468b842f1be8104b7909ec13a&amp;elqaid=26659&amp;elqat=1" style="font-family:Overpass,Arial,Helvetica,sans-serif;font-size:12px;line-height:15px;color:#666666;text-decoration:none" target="_blank" data-saferedirecturl="https://www.google.com/url?hl=zh-CN&amp;q=http://app.engage.redhat.com/e/er?s%3D1795%26lid%3D18901%26elqTrackId%3D09a0bde0d86646b7af860bbe3dbde41b%26elq%3De6d1559468b842f1be8104b7909ec13a%26elqaid%3D26659%26elqat%3D1&amp;source=gmail&amp;ust=1463648584447000&amp;usg=AFQjCNFM5tzKKqecU5lv5URcW-bWLWwNGQ"><font style="font-family:Overpass,Arial,Helvetica,sans-serif;font-size:12px;line-height:15px;color:#666666;text-decoration:none">��ϵ���ǵ������Ŷ�</font></a>&nbsp;&nbsp;|&nbsp;&nbsp;
 <a href="https://www.redhat.com/wapps/ugc/email-subscriptions.html?elqc=78&amp;elqTrackId=6553fd0360864688b7d44504bb49369e&amp;elq=e6d1559468b842f1be8104b7909ec13a&amp;elqaid=26659&amp;elqat=1&amp;elqCampaignId=109736" style="font-family:Overpass,Arial,Helvetica,sans-serif;font-size:12px;line-height:15px;color:#666666;text-decoration:none" target="_blank" data-saferedirecturl="https://www.google.com/url?hl=zh-CN&amp;q=https://www.redhat.com/wapps/ugc/email-subscriptions.html?elqc%3D78%26elqTrackId%3D6553fd0360864688b7d44504bb49369e%26elq%3De6d1559468b842f1be8104b7909ec13a%26elqaid%3D26659%26elqat%3D1%26elqCampaignId%3D109736&amp;source=gmail&amp;ust=1463648584448000&amp;usg=AFQjCNFIK6I6LfpeAFVRZQSN0r_FvLTz8g"> <font style="font-family:Overpass,Arial,Helvetica,sans-serif;font-size:12px;line-height:15px;color:#666666;text-decoration:none">����������Ŷ�����ѡ��</font></a>&nbsp;&nbsp;|&nbsp;&nbsp;<a href="http://app.engage.redhat.com/e/er?s=1795&amp;lid=19231&amp;elqTrackId=eff1feeb848643f18c4fa22741a3671c&amp;elq=e6d1559468b842f1be8104b7909ec13a&amp;elqaid=26659&amp;elqat=1" style="font-family:Overpass,Arial,Helvetica,sans-serif;font-size:12px;line-height:15px;color:#666666;text-decoration:none" target="_blank" data-saferedirecturl="https://www.google.com/url?hl=zh-CN&amp;q=http://app.engage.redhat.com/e/er?s%3D1795%26lid%3D19231%26elqTrackId%3Deff1feeb848643f18c4fa22741a3671c%26elq%3De6d1559468b842f1be8104b7909ec13a%26elqaid%3D26659%26elqat%3D1&amp;source=gmail&amp;ust=1463648584448000&amp;usg=AFQjCNFIzAB2FnNUhH4Sdf3ZQ0qTpAzEhg">
<font style="font-family:Overpass,Arial,Helvetica,sans-serif;font-size:12px;line-height:15px;color:#666666;text-decoration:none">�Ķ���ñ�ı���Э��</font></a>&nbsp;&nbsp;|&nbsp;&nbsp; <a href="https://www.redhat.com/wapps/ugc/master-unsubscribe.html?elqc=78&amp;elqTrackId=01fd643bd4444decb2e3dcee9a57046b&amp;elq=e6d1559468b842f1be8104b7909ec13a&amp;elqaid=26659&amp;elqat=1&amp;elqCampaignId=109736" style="font-family:Overpass,Arial,Helvetica,sans-serif;font-size:12px;line-height:15px;color:#666666;text-decoration:none" target="_blank" data-saferedirecturl="https://www.google.com/url?hl=zh-CN&amp;q=https://www.redhat.com/wapps/ugc/master-unsubscribe.html?elqc%3D78%26elqTrackId%3D01fd643bd4444decb2e3dcee9a57046b%26elq%3De6d1559468b842f1be8104b7909ec13a%26elqaid%3D26659%26elqat%3D1%26elqCampaignId%3D109736&amp;source=gmail&amp;ust=1463648584448000&amp;usg=AFQjCNEqc5pVA8jZgGgWgr6hm4PvwbUb7w"> <font style="font-family:Overpass,Arial,Helvetica,sans-serif;font-size:12px;line-height:15px;color:#666666;text-decoration:none">�˶����к�ñ�����ʼ�</font></a><br>
                  <br>
                  "��ñ"��"Shadowman"<wbr>��ʶ���̱���ñ��˾��ע���̱꣬<br>
                  Linux��Linus Torvalds��ע���̱ꡣ <br>
                  <br>
                  ? 2016���ñ��˾��������Ȩ����<br>
                  <br>
                  ��ñ���л����칫��ַ��<br>
                  �����г�����������·9���ȸ����ݵش���A ��8��<br>
                  �ʱ�: 100020 �绰: <font style="color:#666666;text-decoration:none">8610 65339300</font></td>
                <td width="25" height="10" valign="top" align="left"><img src="https://ci3.googleusercontent.com/proxy/PmiJRizlbfNJbygMXAAIf_YCMx3yywsuZRR2hzmJMypwofBNFOHvAf-ws8_2NTUEkheZcUBJztE7XPIPzzkgUGIIIzWj3Tn1sLh6-p8BXOlMO_nf4tZ5z1jFvadH6ARz5rxMoDix1SCiwWX2ZRtpm5kHA8Io9JlbAGEekhIT0btv0A=s0-d-e1-ft#http://images.engage.redhat.com/EloquaImages/clients/RedHat/%7b217d48d9-b987-444f-a169-e51ab03a95a1%7d_s.gif" width="25" height="10" border="0" alt="" style="display:block" class="CToWUd"></td>
              </tr>
              <tr>
                <td width="25" height="40" valign="top" align="left" style="line-height:40px"><img src="https://ci3.googleusercontent.com/proxy/PmiJRizlbfNJbygMXAAIf_YCMx3yywsuZRR2hzmJMypwofBNFOHvAf-ws8_2NTUEkheZcUBJztE7XPIPzzkgUGIIIzWj3Tn1sLh6-p8BXOlMO_nf4tZ5z1jFvadH6ARz5rxMoDix1SCiwWX2ZRtpm5kHA8Io9JlbAGEekhIT0btv0A=s0-d-e1-ft#http://images.engage.redhat.com/EloquaImages/clients/RedHat/%7b217d48d9-b987-444f-a169-e51ab03a95a1%7d_s.gif" width="25" height="40" border="0" alt="" style="display:block" class="CToWUd"></td>
                <td width="590" height="40" align="left" valign="top" style="line-height:40px"><img src="https://ci3.googleusercontent.com/proxy/PmiJRizlbfNJbygMXAAIf_YCMx3yywsuZRR2hzmJMypwofBNFOHvAf-ws8_2NTUEkheZcUBJztE7XPIPzzkgUGIIIzWj3Tn1sLh6-p8BXOlMO_nf4tZ5z1jFvadH6ARz5rxMoDix1SCiwWX2ZRtpm5kHA8Io9JlbAGEekhIT0btv0A=s0-d-e1-ft#http://images.engage.redhat.com/EloquaImages/clients/RedHat/%7b217d48d9-b987-444f-a169-e51ab03a95a1%7d_s.gif" width="590" height="40" border="0" alt="" style="display:block" class="CToWUd"></td>
                <td width="25" height="40" valign="top" align="left" style="line-height:40px"><img src="https://ci3.googleusercontent.com/proxy/PmiJRizlbfNJbygMXAAIf_YCMx3yywsuZRR2hzmJMypwofBNFOHvAf-ws8_2NTUEkheZcUBJztE7XPIPzzkgUGIIIzWj3Tn1sLh6-p8BXOlMO_nf4tZ5z1jFvadH6ARz5rxMoDix1SCiwWX2ZRtpm5kHA8Io9JlbAGEekhIT0btv0A=s0-d-e1-ft#http://images.engage.redhat.com/EloquaImages/clients/RedHat/%7b217d48d9-b987-444f-a169-e51ab03a95a1%7d_s.gif" width="25" height="40" border="0" alt="" style="display:block" class="CToWUd"></td>
              </tr>
            </tbody>
          </table>

          </td>
      </tr>
    </tbody>
  </table>
</div>


<br>

<img src="https://ci6.googleusercontent.com/proxy/MnvTiEuQC74dQ9nhRehzbYnhGDc2MVde01zM2k9KnNqs1IWaGjwr2xpVNDqmqikMh0rk56oBatfUaUYDUiXEmaLIrpz88VEQafr1AGQgtXqu4oLHx-1bPKLGTqszIOIkdt4maMJh45epb734G0vOt4IL8iOX5Wby0wsF4_KJBA=s0-d-e1-ft#http://app.engage.redhat.com/e/FooterImages/FooterImage1?elq=e6d1559468b842f1be8104b7909ec13a&amp;siteid=1795" alt="" border="0" width="1px" height="1px" class="CToWUd"></div></div><div class="yj6qo"></div></div><div id=":nh" class="ii gt" style="display:none"><div id=":mm" class="a3s aXjCH undefined"></div></div><div class="hi"></div></div><div class="ajx"></div></div><div class="gA gt acV"><div class="gB xu"><table id=":l7" cellpadding="0" role="presentation" class="cf gz ac0"><tbody><tr><td><div class="cKWzSc mD" idlink="" tabindex="0" role="button"><img class="mL" src="images/cleardot.gif" alt=""> <span class="mG">�ظ�</span></div></td><td></td><td><div class="XymfBd mD" idlink="" tabindex="0" role="button"><img class="mI" src="images/cleardot.gif" alt=""> <span class="mG">ת��</span></div></td><td></td><td class="io"><div class="adA"></div></td></tr></tbody></table><div class="ip iq"><div id=":mz"><table class="cf FVrZGe" role="presentation"><tbody><tr><td class="amq"><img id=":0_3" name=":0" src="https://ssl.gstatic.com/ui/v1/icons/mail/no_photo.png" jid="zhangming025251@gmail.com" class="ajn bofPge"></td><td class="amr"><div class="nr tMHS5d"><div class="amn">����˴���<span id=":ld" class="ams" role="link" tabindex="0">�ظ�</span>��<span id=":lb" class="ams" role="link" tabindex="0">ת��</span></div></div><input type="text" class="amp"></td></tr></tbody></table></div></div></div></div></div></div></div></div></div></div><div class="nH"></div><div class="nH"><div class="nH PS" style="display: none;"></div></div></div></div> '''):
        print "���ͳɹ�"
    else:
        print "����ʧ��"