#ifndef __BASE_NET_THREAD_H__
#define __BASE_NET_THREAD_H__

#include "common_def.h"
#include "base_thread.h"
#include "common_obj_container.h"
#include "base_connect.h"
#include "channel_data_process.h"


class base_net_container;
class base_net_thread:public base_thread
{
    public:
        base_net_thread(int channel_num = 1);
        virtual ~base_net_thread();

        virtual void *run();

        virtual void run_process();

        virtual void net_thread_init();

        virtual void put_msg(uint32_t obj_id, std::shared_ptr<normal_msg> & p_msg);

        static void put_obj_msg(ObjId & id, std::shared_ptr<normal_msg> & p_msg);

        virtual void handle_msg(std::shared_ptr<normal_msg> & p_msg);

        static base_net_thread * get_base_net_thread_obj(uint32_t thread_index);

        void add_timer(std::shared_ptr<timer_msg> & t_msg);

        virtual void handle_timeout(std::shared_ptr<timer_msg> & t_msg);

        common_obj_container * get_net_container();

    protected:

        int _channel_num;
        std::vector< std::shared_ptr<base_connect<channel_data_process> > > _channel_msg_vec;

        common_obj_container * _base_container;

        static std::unordered_map<uint32_t, base_net_thread *> _base_net_thread_map;
};

#endif
