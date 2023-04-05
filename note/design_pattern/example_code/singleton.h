#ifndef __SINGLETON_H__
#define __SINGLETON_H__

#include <iostream>
using namespace std;

class LOCK
{
    public:
        LOCK(){}
        ~LOCK(){}
};

class SINGLETON
{
    public:
        static SINGLETON * get_instance();
        ~SINGLETON() {}
    private:
        SINGLETON() { cout <<"SINGLETON()"<<endl;}
        static SINGLETON * _instance;
};

#endif