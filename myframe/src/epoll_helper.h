#ifndef __EPOLL_HELPER__
#define __EPOLL_HELPER__

#include "def.h"

namespace MZFRAME {

    class epoll_helper{
        
        public:
            epoll_helper();
            ~epoll_helper();
            void init(const uint32_t epoll_size = 0, const uint32_t epoll_wait_time)

            void add_to_epoll(base_net_obj *p_obj);
            void del_from_epoll(base_net_obj *p_obj);
            void mod_from_epoll(base_net_obj *p_obj);			
			int epoll_wait();

        private:
            int _epoll_fd;
            struct epoll_event *_epoll_events;
            uint32_t _real_epoll_size;
			uint32_t _real_epoll_wait_time;
    };
    
}



#endif
