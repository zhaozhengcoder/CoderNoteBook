#include <cstddef>
#include "memory_op.h"
#include "macro.h"

int test_func2()
{
    {
        int * q1 = new int();
        delete q1;
    }
    return 0;
}