#ifndef __PROC_DATA_H__
#define __PROC_DATA_H__

#include "base_reload.h"
#include "sk_conf.h"
#include "base_net_thread.h"

class ua_dict;
class strategy_dict;
class finance_dict;
class ban_dict;
class id_dict;
class proc_data:public reload_inf
{
    public:
        virtual ~proc_data(){}
        
        static proc_data * instance();

        int init(sk_conf *conf);
        virtual int load();
        virtual int reload();
        virtual bool need_reload();
        virtual int dump();
        virtual int destroy();

    public:
        reload_mgr<ua_dict> * _ua_dict;
        reload_mgr<id_dict> * _id_dict;
        //reload_mgr<real_rdict> * _real_dict;

        reload_mgr<strategy_dict> * _strategy_dict;

        sk_conf * _conf;

    public:
        reload_mgr<finance_dict> * _finance_dict;

        reload_mgr<ban_dict> * _ban_dict;

        //reload_mgr<history_single_t> * _hsingle_dict;

        //reload_mgr<history_quotation_t> * _hquoation_dict;


    private:
        static proc_data* _singleton;
};


#endif
