#include <iostream>
#include "module_a.h"

int func_a(int &val)
{
    if (val > 100)
    {
        val = val * 100;
    }
    else 
    {
        val++;
    }
    return 0;
}