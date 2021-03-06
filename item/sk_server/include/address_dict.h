#ifndef __address_dict_H_
#define __address_dict_H_

#include "base_reload.h"
#include "sk_def.h"

class address_dict:public reload_inf
{
    public:
        virtual ~address_dict();
        address_dict();

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
        std::unordered_map<std::string, std::vector<std::string>, str_hasher> _id_dict;

        std::unordered_map<std::string, std::vector<std::string>, str_hasher> _address_index;
};



#endif
