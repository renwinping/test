#include "addr_dict_split.h"
#include "base_def.h"
#include "log_helper.h"
#include "ul_sign.h"
#include "common_util.h"
#include "proc_data.h"

addr_dict_split::addr_dict_split()
{
}

addr_dict_split::~addr_dict_split()
{
    destroy();
}

int addr_dict_split::init(const char * path, const char * file, const char *dump_dir)
{
    snprintf(_fullpath, sizeof(_fullpath), "%s/%s", path, file);
    snprintf(_dumppath, sizeof(_dumppath), "%s/%s", dump_dir, file);

    destroy();

    return 0;
}

int addr_dict_split::load()
{
    proc_data* p_data = proc_data::instance();
    FILE * fp = fopen(_fullpath, "r");
    ASSERT_WARNING(fp != NULL,"open query dict failed. path[%s]", _fullpath);

    char line[SIZE_LEN_1024];
    char * ptr = NULL;
    uint32_t query_sign[2];

    while (fgets(line, 1024, fp)) 
    {
        if('\0' == line[0]){
            continue;
        }
        //line[strlen(line) - 1] = '\0';
        ptr = im_chomp(line);
        if (ptr == NULL || *ptr == '\0'|| *ptr == '#')
            continue;

        std::vector<std::string> tmp_vec;
        SplitString(ptr, '\t', &tmp_vec, SPLIT_MODE_ALL);
        if (tmp_vec.size() < 2)
        {
            continue;
        }
        
        std::string id = *(tmp_vec.begin());
        tmp_vec.erase(tmp_vec.begin());

        for (auto iit = tmp_vec.begin(); iit != tmp_vec.begin(); iit++) 
        {   
            auto iii =  p_data->_address_index.idle()->find(*iit);
            if (iii != p_data->_address_index.idle()->end())
            {   
                iii->second.push_back(id);
            }   
            else
            {   
                std::vector<std::string> id_vec;
                id_vec.push_back(id);
                p_data->_address_index.idle()->insert(std::make_pair(*iit, id_vec));
            }   
        }
    }

    fclose(fp);
    struct stat st;
    stat(_fullpath, &st);
    _last_load = st.st_mtime;

    p_data->_address_index.idle_2_current();

    return 0;
}

int addr_dict_split::reload()
{
    proc_data* p_data = proc_data::instance();
    {
        std::unordered_map<std::string, std::vector<std::string>, str_hasher> tmp;
        p_data->_address_index.idle()->swap(tmp);
    }

    return load();
}

void addr_dict_split::set_path (const char* path)
{
    snprintf(_fullpath, sizeof(_fullpath), "%s", path);
}

bool addr_dict_split::need_reload()
{
    struct stat st;

    if (stat(_fullpath, &st) == 0 && S_ISREG(st.st_mode) && st.st_mtime != _last_load)
    {
        return true;
    }

    return false;
}

int addr_dict_split::dump()
{
    return 0;
}

int addr_dict_split::destroy()
{

    return 0;
}

