#ifndef __BAN_DICT_H_
#define __BAN_DICT_H_

#include "base_reload.h"
#include "inc_dict.h"
#include "sk_def.h"

class ban_dict:public reload_inf
{
    public:
        virtual ~ban_dict(){}

        virtual int init(const char * path, uint32_t query_num);
        virtual int load();
        virtual int reload();
        virtual bool need_reload();
        virtual int dump();
        virtual int destroy();

    private:
        void set_path (const char* path);

    private:
        char _fullpath[SIZE_LEN_512];
        time_t _last_load;
    public:
        inc_dict_t<ban_t> _id_dict;
};



#endif