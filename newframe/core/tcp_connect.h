#ifndef __TCP_CONNECT_H__
#define __TCP_CONNECT_H__

#include "log_helper.h"
#include "common_connect.h"
#include "base_net_thread.h"
#include "common_def.h"
#include "tcp_connect.h"

class base_net_thread;
class tcp_connect:public common_connect
{
    public:

        tcp_connect(int32_t sock, base_net_thread * thread):common_connect(sock, thread), _recv_buf_len(0)
        {
        }

        virtual ~tcp_connect();

        virtual void call_back(int fd, short ev, void *arg);

        void real_recv();

        virtual int RECV(void *buf, size_t len);

        void real_send();

        virtual ssize_t SEND(const void *buf, const size_t len);

        virtual size_t process_recv_buf(char *buf, size_t len);

        virtual size_t process_s(char *buf, size_t len);

        virtual size_t process_send_buf(char *buf, size_t len);
        
        virtual void peer_close();

        virtual void error_back();

    protected:
        string _recv_buf;
        size_t _recv_buf_len;

        string _send_buf;
};


#endif