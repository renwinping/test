#ifndef __COMMON_UTIL_H__
#define __COMMON_UTIL_H__

#include "base_def.h"

void get_proc_name(char buf[], size_t buf_len);

template<class OBJ>
class REC_OBJ
{
    public:
        REC_OBJ(OBJ * p_obj):_p_obj(p_obj){}
        ~REC_OBJ(){
            if (_p_obj){
                delete _p_obj;
            }   
        }   
    private:
        OBJ *_p_obj;
};

int get_prime_num(int num);

int SplitString(const string &srcStr,const string &delim, vector<string>& strList);

int SplitString(const char *srcStr, string &delim, vector<string>& strList);

int SplitfirstDelimString(const string &srcStr,const string &delim, vector<string>& strList);

void StringTrim(string &sSrc);

int GetCaseStringByLabel(const string &sSrc,const string &sLabel1,const string &sLabel2, string &sOut, unsigned int nBeginPos, int nIfRetPos);

int GetStringByLabel(const string &sSrc,const string &sLabel1,const string &sLabel2, string &sOut, unsigned int nBeginPos, int nIfRetPos);

uint64_t ntohl64(uint64_t src);

uint64_t htonl64(uint64_t src);

void set_unblock(int fd);

uint64_t GetMilliSecond();

time_t get_date_str(char dest[], size_t dest_len, const char * format);

int UrlEncode(const string &sSrc, string &sDest);

int UrlDecode(const string &sSrc, string &sDest);


#define ASSERT_DO(valid, PRINT) \
    do{ \
        if (!(valid)) { \
            (PRINT); \
            return -1; \
        } \
    }while(0)

#define ASSERT(valid) \
    do { \
        if (!(valid)) { \
            return -1; \
        } \
    }while(0)
    
    
#ifdef DEBUG
#define PDEBUG(format, arg...) \
    do { \
        printf("tid:[%lu],line:[%d],func:[%s],file:[%s] "format, pthread_self(), __LINE__, __func__, __FILE__, ##arg); \
} while (0)
#else
    #define PDEBUG(format, arg...) 
#endif



#endif