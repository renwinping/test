#ifndef __end_end10_SEARCH_INDEX_H__
#define __end_end10_SEARCH_INDEX_H__

#include "sk_def.h"
#include "common_util.h"

class end_end10_search_index:public base_search_index, public ToBufferMgr<std::multimap<float, std::string> >
{
    public:
        virtual ~end_end10_search_index(){}

        virtual bool search(std::string &key, std::string &value, std::set<std::string> & search);

        bool do_check_end_end10_le(std::string &key, std::string &value, std::set<std::string> & search);

        bool do_check_end_end10_ge(std::string &key, std::string &value, std::set<std::string> & search);

};


#endif

