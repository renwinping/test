#ifndef __DEF_H__
#define __DEF_H__

#include <stdint.h>

#include <stdio.h>
#include <errno.h> 
#include <string.h>
#include <sys/epoll.h>

#include <pthread.h>
#include <vector>

#include <map>

#include <sys/types.h>
#include <sys/socket.h>



static const uint32_t SIZE_LEN_16 = 16; 
static const uint32_t SIZE_LEN_32 = 32; 
static const uint32_t SIZE_LEN_64 = 64; 
static const uint32_t SIZE_LEN_128 = 128; 
static const uint32_t SIZE_LEN_256 = 256; 

#define ASSERT_DO(valid, PRINT) \
    do{ \
        if (!(valid)) { \
            (PRINT); \
            return -1; \
        } \
    }while(0)

#define ASSERT(valid) \
    do{ \
        if (!(valid)) { \
            return -1; \
        } \
    }while(0)


#endif