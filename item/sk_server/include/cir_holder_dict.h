#ifndef _cir_holder_DICT_H_
#define _cir_holder_DICT_H_

#include "base_reload.h"
#include "sk_def.h"

class cir_holder_dict:public reload_inf
{
    public:
        virtual ~cir_holder_dict();
        cir_holder_dict();

        virtual int init(const char * path, const char * file, const char *dump_dir);
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
        std::unordered_map<std::string, std::vector<std::shared_ptr<std::string> >, str_hasher, str_equaler> _id_dict;
        std::unordered_set<std::shared_ptr<std::string>, str_hasher, str_equaler> _cir_holder_set;
};



#endif
