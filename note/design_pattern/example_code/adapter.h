#ifndef __ADAPTER_H__
#define __ADAPTER_H__

#include <iostream>
using namespace std;

class OLD_CLASS
{
    public:
        virtual void dosomething() {cout<<"do something OLD_CLASS"<<endl; }
    private:
        int _data;
};

class NEW_CLASS
{
    public:
        void dosomething() {cout<<"do something NEW_CLASS"<<endl; }
    private:
        int _data;
};

class Adapter : public OLD_CLASS
{
    public:
        Adapter(NEW_CLASS * new_obj):_new_obj(new_obj) {}

        void dosomething() 
        {
            _new_obj->dosomething();
        }

    private:
        NEW_CLASS * _new_obj;
};

#endif