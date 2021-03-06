#include "common_epoll.h"
#include "base_net_obj.h"
#include "common_exception.h"
#include "log_helper.h"


void common_epoll::add_to_epoll(base_net_obj * p_obj)
{		
    int tmpOprate = EPOLL_CTL_ADD;
    struct epoll_event tmpEvent;
    memset(&tmpEvent, 0, sizeof(epoll_event));
    tmpEvent.events = p_obj->get_event();
    tmpEvent.data.ptr = p_obj;
    int ret = epoll_ctl(_epoll_fd, tmpOprate, p_obj->get_sfd(), &tmpEvent);
    LOG_DEBUG("add to epoll _epoll_fd[%d] _get_sock [%d]", _epoll_fd, p_obj->get_sfd());
    if (ret != 0) {
        LOG_DEBUG("add to epoll fail %s", strerror(errno));
        THROW_COMMON_EXCEPT("add to epoll fail " << strerror(errno));
    }
}

void common_epoll::del_from_epoll(base_net_obj * p_obj)
{	
    int tmpOprate = EPOLL_CTL_DEL;
    struct epoll_event tmpEvent;
    memset(&tmpEvent, 0, sizeof(epoll_event));
    tmpEvent.data.ptr = p_obj;;
    int ret = epoll_ctl(_epoll_fd, tmpOprate, p_obj->get_sfd(), &tmpEvent);
    LOG_DEBUG("delete to epoll _epoll_fd[%d] _get_sock [%d]", _epoll_fd, p_obj->get_sfd());
    if (ret != 0)
        THROW_COMMON_EXCEPT("del from epoll fail " << strerror(errno));
}

void common_epoll::mod_from_epoll(base_net_obj * p_obj)
{
    int tmpOprate = EPOLL_CTL_MOD;
    struct epoll_event tmpEvent;
    tmpEvent.events =  p_obj->get_event();  
    tmpEvent.data.ptr = p_obj;
    int ret = epoll_ctl(_epoll_fd, tmpOprate, p_obj->get_sfd(), &tmpEvent);
    if (ret != 0)
        THROW_COMMON_EXCEPT("mod from epoll fail "<< strerror(errno));
}

int common_epoll::epoll_wait(std::map<ObjId, std::shared_ptr<base_net_obj> > &expect_list, std::map<ObjId, std::shared_ptr<base_net_obj> > &remove_list, uint32_t num)
{
    int  nfds = ::epoll_wait(_epoll_fd, _epoll_events, _epoll_size, _epoll_wait_time);
    if (nfds == -1)
    {
        LOG_DEBUG("epoll_wait fail [%s]", strerror(errno));          
        if (errno == EINTR)
            return 0;
        THROW_COMMON_EXCEPT("epoll_wait fail "<< strerror(errno));          
    }      

    for (int i =0; i < nfds; i++)
    {		
        //LOG_DEBUG("epoll_fd [%d]\n", _epoll_fd);
        if (_epoll_events[i].data.ptr != NULL) 		
        {
            base_net_obj * p = (base_net_obj*)(_epoll_events[i].data.ptr);
            if (p != NULL)
            {
                std::shared_ptr<base_net_obj> p_obj=std::dynamic_pointer_cast<base_net_obj>(p->shared_from_this());
                try
                {
                    //LOG_DEBUG("get_sock[%d]\n", p->get_sfd());
                    p->event_process(_epoll_events[i].events);
                    if (p->get_real_net()) {
                        remove_list.insert(std::make_pair(p->get_id(), p_obj));
                    }
                }
                catch(CMyCommonException &e)
                {
                    expect_list.insert(std::make_pair(p->get_id(), p_obj));
                }
                catch(std::exception &e)
                {
                    expect_list.insert(std::make_pair(p->get_id(), p_obj));
                }
            }
        }
    }
    return nfds;
}
