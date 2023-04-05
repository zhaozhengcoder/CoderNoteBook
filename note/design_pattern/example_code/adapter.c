#include <iostream>
#include "adapter.h"

using namespace std;

int func(OLD_CLASS * old)
{
    old->dosomething();
    return 0;
}

int adapter_demo(NEW_CLASS * new_obj)
{
    // 比如说直接调用因为参数不对而报错
    // func(new)

    Adapter adapter(new_obj);
    adapter.dosomething();

    return 0;
}