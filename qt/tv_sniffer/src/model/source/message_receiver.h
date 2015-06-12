
/** 
 * Copyright (C) 2007-2013 Haier
 *
 * @file             message_receiver.h
 * @brief            ��Ϣ������
 * @author           zhengyl
 * @version	         1.0
 * @date	         2014-1-24
 */
#ifndef  _RECEIVER_MSG_THREAD_H_
#define  _RECEIVER_MSG_THREAD_H_
#include <QObject>
class QUdpSocket;
class IModel;
class CPacketsCache;
class CStatisticsThread;

class  CMessageReceiver : public QObject
{
    Q_OBJECT
public:
    CMessageReceiver (
        QUdpSocket * udp_socket,
        CPacketsCache * cache,
        CStatisticsThread * statistics_thread
        );
    ~CMessageReceiver ();

protected:

private:
    /** ������
     * 
     * @param  datagram ����
     * @return void
     * @see 
     * @note 
     */
    void processTheDatagram (const QByteArray & datagram);

private:
    QUdpSocket * m_udp_socket;
    CPacketsCache * m_packets_cache;
    CStatisticsThread * m_statistics_thread;
private slots:

    /** �Ķ�����ı���
     * 
     * @return void
     * @see 
     * @note 
     */
    void readPendingDatagrams ();
    
};

#endif