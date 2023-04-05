#include <iostream>
#include "module_b.h"

int func_b(int &val)
{
    if (val > 500)
    {
        val = val * 500;
    }
    else 
    {
        val++;
    }
    return 0;
}