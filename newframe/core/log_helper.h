#ifndef __LOG_HELPER_H_
#define __LOG_HELPER_H_

#include "log_thread.h"
#include "common_def.h"
#include "base_singleton.h"

#define LOG_INIT(log_conf) \
    do { \
        log_thread * thread = base_singleton<log_thread>::get_instance(); \
        if (thread) { \
            break; \
        } \
        thread = new log_thread(conf); \
        base_singleton<log_thread>::set_instance(thread); \
        thread->start(); \
        sleep(1); \
    }  while (0)

#define LOG_WARNING(fmt, arg...) \
    do { \
        log_thread * thread = base_singleton<log_thread>::get_instance(); \
        if (!thread) { \
            break; \
        } \
        if (LOGWARNING > thread->get_log_conf().type) { \
            break; \
        } \
        {\
            log_msg * lgmsg =  new log_msg(); \
            char log_common_tmp[SIZE_LEN_64]; \
            get_date_str(log_common_tmp, sizeof(log_common_tmp), LOG_DATE_FORMAT); \
            lgmsg->type = LOGWARNING; \
            lgmsg->tid = pthread_self(); \
            lgmsg->_op = PASSING_LOG; \
            char log_common_buf[SIZE_LEN_16384]; \
            snprintf(log_common_buf, sizeof(log_common_buf), "[WARNING]"":[%s]:[%lu]:[%d:%s:%s] "fmt,log_common_tmp,pthread_self(), __LINE__, __func__, __FILE__, ##arg); \
            lgmsg->str.append(log_common_buf); \
            thread->add_msg(lgmsg); \
        }\
    } while (0)


#define LOG_FATAL(fmt, arg...) \
              do { \
        log_thread * thread = base_singleton<log_thread>::get_instance(); \
        if (!thread) { \
            break; \
        } \
        if (LOGFATAL > thread->get_log_conf().type) { \
            break; \
        } \
        {\
            log_msg * lgmsg =  new log_msg(); \
            char log_common_tmp[SIZE_LEN_64]; \
            get_date_str(log_common_tmp, sizeof(log_common_tmp), LOG_DATE_FORMAT); \
            lgmsg->type = LOGFATAL; \
            lgmsg->tid = pthread_self(); \
            lgmsg->_op = PASSING_LOG; \
            char log_common_buf[SIZE_LEN_16384]; \
            snprintf(log_common_buf, sizeof(log_common_buf), "[FATAL]"":[%s]:[%lu]:[%d:%s:%s] "fmt, log_common_tmp,pthread_self(), __LINE__, __func__, __FILE__, ##arg); \
            lgmsg->str.append(log_common_buf); \
            thread->add_msg(lgmsg); \
        }\
    } while (0)


#define LOG_NOTICE(fmt, arg...) \
            do { \
        log_thread * thread = base_singleton<log_thread>::get_instance(); \
        if (!thread) { \
            break; \
        } \
        if (LOGNOTICE > thread->get_log_conf().type) { \
            break; \
        } \
        {\
            log_msg * lgmsg =  new log_msg(); \
            char log_common_tmp[SIZE_LEN_64]; \
            get_date_str(log_common_tmp, sizeof(log_common_tmp), LOG_DATE_FORMAT); \
            lgmsg->type = LOGNOTICE; \
            lgmsg->tid = pthread_self(); \
            lgmsg->_op = PASSING_LOG; \
            char log_common_buf[SIZE_LEN_16384]; \
            snprintf(log_common_buf, sizeof(log_common_buf), "[NOTICE]"":[%s]:[%lu]:[%d:%s:%s] "fmt,log_common_tmp,pthread_self(), __LINE__, __func__, __FILE__, ##arg); \
            lgmsg->str.append(log_common_buf); \
            thread->add_msg(lgmsg); \
        }\
    } while (0)


#define LOG_TRACE(fmt, arg...) \
    do { \
        log_thread * thread = base_singleton<log_thread>::get_instance(); \
        if (!thread) { \
            break; \
        } \
        if (LOGTRACE > thread->get_log_conf().type) { \
            break; \
        } \
        {\
            log_msg * lgmsg =  new log_msg(); \
            char log_common_tmp[SIZE_LEN_64]; \
            get_date_str(log_common_tmp, sizeof(log_common_tmp), LOG_DATE_FORMAT); \
            lgmsg->type = LOGTRACE; \
            lgmsg->tid = pthread_self(); \
            lgmsg->_op = PASSING_LOG; \
            char log_common_buf[SIZE_LEN_16384]; \
            snprintf(log_common_buf, sizeof(log_common_buf), "[TRACE]"":[%s]:[%lu]:[%d:%s:%s] "fmt,log_common_tmp,pthread_self(), __LINE__, __func__, __FILE__, ##arg); \
            lgmsg->str.append(log_common_buf); \
            thread->add_msg(lgmsg); \
        }\
    } while (0)


#define LOG_DEBUG(fmt, arg...) \
    do { \
        log_thread * thread = base_singleton<log_thread>::get_instance(); \
        if (!thread) { \
            break; \
        } \
        if (LOGDEBUG > thread->get_log_conf().type) { \
            break; \
        } \
        {\
            log_msg * lgmsg =  new log_msg(); \
            char log_common_tmp[SIZE_LEN_64]; \
            get_date_str(log_common_tmp, sizeof(log_common_tmp), LOG_DATE_FORMAT); \
            lgmsg->type = LOGDEBUG; \
            lgmsg->tid = pthread_self(); \
            lgmsg->_op = PASSING_LOG; \
            char log_common_buf[SIZE_LEN_16384]; \
            snprintf(log_common_buf, sizeof(log_common_buf), "[DEBUG]"":[%s]:[%lu]:[%d:%s:%s] "fmt,log_common_tmp,pthread_self(), __LINE__, __func__, __FILE__, ##arg); \
            lgmsg->str.append(log_common_buf); \
            thread->add_msg(lgmsg); \
        }\
    } while (0)

#endif