#ifndef __PERF_COLLECT_H__
#define __PERF_COLLECT_H__

#include "perf_stat.h"
#include "perf_stat_str_def.h"

/*
主频是1MHZ的话，那么TSC就会在1秒内增加1000000;

$ cat /proc/cpuinfo | grep MHz | uniq
cpu MHz : 2494.140

1秒跑下来的tsc = 2494412210
*/

class CYCLE_PROFILER
{
public:
    CYCLE_PROFILER(int id) : _id(id)
    {
        rdtscll(_tsc_begin);
    }

    ~CYCLE_PROFILER()
    {
        rdtscll(_tsc_end);
        unsigned long int time = _tsc_end - _tsc_begin;
        printf("func id : %s, begin %lu, end %lu, use cpu tsc %lu \n", stat_type_str[_id], _tsc_begin, _tsc_end, time);
    }

private:
    int _id;
    unsigned long int _tsc_begin;
    unsigned long int _tsc_end;
};

#endif