#include <iostream>
#include <memory>
#include "test1.h"
#include "test2.h"

using namespace std;

struct A {
    int a;
};

int main()
{
    test_func1();
    test_func2();

    cout << "=====" << endl;
    {
        int * q1 = new int();
        delete q1;
    }
    {
        std::cout <<"\nshared ptr" << std::endl;
        shared_ptr<A> a = make_shared<A>();
    }

    // int * p = new(__FILE__, __LINE__) int;
    // int * q = new int();
    // int * arr = new int[10];

    // delete p;
    // delete q;
    // delete arr;

    // {
    //     int * q1 = new int();
    //     delete q1;
    // }
    // {
    //     int * q2 = new int();
    //     delete q2;
    // }

    // {
    //     cout << "test shared ptr" <<endl;
    //     shared_ptr<A> a = make_shared<A>();
    // }
    return 0;
}

// g++ main.cpp test1.cpp test2.cpp memory_op.cpp -Wl,-wrap=malloc -Wl,-wrap=free