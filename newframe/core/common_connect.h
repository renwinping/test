#ifndef __COMMON_CONNECT_H__
#define __COMMON_CONNECT_H__

#include "base_net_thread.h"
#include "common_def.h"
#include "base_connect.h"

class base_net_thread;
class common_connect:public base_connect
{
    public:

        common_connect(int32_t sock, base_net_thread * thread):base_connect(thread), _fd(sock), _ev(0)
        {
            
        }

        virtual ~common_connect()
        {
            close();
        }

        void close();

        int get_sock();

        void get_local_addr(sockaddr_in &addr);

        virtual void call_back(int fd, short ev, void *arg) = 0;

        static void on_cb(int fd, short ev, void *arg);

        bool update_event(short ev);

        short get_ev_flags();

    protected:
        int _fd;
        short _ev;
        struct event _event;
};


#endif