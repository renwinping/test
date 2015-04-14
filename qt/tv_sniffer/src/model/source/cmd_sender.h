/** 
 * Copyright (C) 2007-2013 Haier
 *
 * @file             cmd_sender.h
 * @brief            �������
 * @author           zhengyl
 * @version	         1.0
 * @date	         2014-1-24
 */
#ifndef  _CMD_SENDER_H_
#define  _CMD_SENDER_H_
class QUdpSocket;

class CMDSender
{
public:
    CMDSender (QUdpSocket * udp_socket);
    /** ��tshark���̷�������
     * 
     * @param  message_type ����
     * @param  content      ����
     * @param  length       ����
     * @return 
     * @see 
     * @note 
     */
    int send (int message_type, char * content = 0, int length = 0);
protected:
private:
    QUdpSocket * m_udp_socket;
};

#endif