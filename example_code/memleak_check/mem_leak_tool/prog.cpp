#include "memery_op.h"
#include <memory>
#include <iostream>
#include "macro.h"

using namespace std;

struct A {
    int a;
};

int main()
{
    {
        int * q1 = new int();
        // delete q1;

        // shared_ptr<A> a = make_shared<A>();
        checkLeaks();
    }
    
    // {
    //     int * q1 = new int();
    //     delete q1;
    // }
    // checkLeaks();
    return 0;
}

// g++ memery_op.cpp prog.cpp