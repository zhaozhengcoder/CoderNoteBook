#include <stdio.h>
#include <unistd.h>
#include "perf_stat_def.h"
#include "perf_collector.h"

int test_func()
{
    CYCLE_PROFILER((int)_type_test_func);

    int times = 1000000;
    while (times > 0)
    {
        int value = times * times;
        times--;
    };
}

int main()
{
    test_func();
    return 0;
}