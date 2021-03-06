#ifndef _STRATEGY_DICT_H_
#define _STRATEGY_DICT_H_

#include "base_reload.h"
#include "common_cfgparser.h"

class strategy_dict:public reload_inf
{
    public:
        virtual ~strategy_dict();
        strategy_dict();

        int init(const char * path, const char * file, const char *dump_dir);
        virtual int load();
        virtual int reload();
        virtual bool need_reload();
        virtual int dump();
        virtual int destroy();

    private:
        void set_path (const char* path);

    private:
        char _fullpath[SIZE_LEN_512];
        char _dumppath[SIZE_LEN_512];
        time_t _last_load;

    public:
        common_cfgparser _cfg;
};



#endif
