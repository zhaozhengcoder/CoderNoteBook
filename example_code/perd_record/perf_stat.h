#ifndef __PERF_STAT_H__
#define __PERF_STAT_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <inttypes.h>

#ifdef __x86_64__
#define rdtscll(val) do {\
        unsigned int __a,__d; \
        asm volatile("rdtsc" : "=a" (__a), "=d" (__d)); \
        (val) = ((unsigned long)__a) | (((unsigned long)__d)<<32); \
    }while(0);
#else   // __x86_64__
    #define rdtscll(val) \
        __asm__ __volatile__("rdtsc" : "=A" (val))
#endif  // __x86_64__

#ifndef _WIN32
    #include <sys/time.h>
#else   // _WIN32
    #pragma warning(disable:4996)
    #pragma comment(lib, "winmm.lib")
    #include <windows.h>
    #define usleep        Sleep

    inline void gettimeofday(struct timeval *tv, void *) {
        unsigned int tt = timeGetTime();
        tv->tv_sec = tt/1000;            // ?
        tv->tv_usec = tt%1000 * 1000;    // ?
    }
#endif  // _WIN32

#define __MEASURE_IN_TICKS__            // 此宏会导致一般情况下会使用tick计量，cpu不支持时则使用gettimeofday计量

#ifdef __MEASURE_IN_TICKS__
    #ifndef _WIN32
        #include <unistd.h>
        #include <sys/types.h>
        #include <fcntl.h>
        #define CPUINFO             "/proc/cpuinfo"
        #define CONSTANT_TSC        "constant_tsc"
    #endif  // _WIN32

    inline int mx_stat_init()
    {
        int ret = -1;

    #ifndef _WIN32
        const size_t BUFFSIZE = 4096;
        int fd = open(CPUINFO, O_RDONLY);   // cat cpu info
        if(0 > fd) return -1;
        do {
            char buff[BUFFSIZE];
            memset(buff, 0, BUFFSIZE);
            ssize_t read_size = read(fd, buff, BUFFSIZE - 1);    // read it
            if (0 > read_size) break;

            char *found_str = strstr(buff, CONSTANT_TSC);
            if (NULL != found_str) {        // found it, TSC supported!
                ret = 0;
                break;
            }
        } while(0);
        close(fd);
    #endif // _WIN32

        return ret;
    }
#endif  // __MEASURE_IN_TICKS__


#endif //__PERF_STAT_H__
