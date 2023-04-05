#ifndef __PERF_STAT_DEF_H__
#define __PERF_STAT_DEF_H__

#ifdef PERF_DECLARE_STAT_TYPE
#undef PERF_DECLARE_STAT_TYPE
#endif

#define PERF_DECLARE_STAT_TYPE(x) x,

enum stat_type_t
{
#include "perf_stat_type_def.h"
    _type_max,
};

#endif