#include "test1.h"

int test_func1()
{
    {
        int * q1 = new int();
        delete q1;
    }
    return 0;
}