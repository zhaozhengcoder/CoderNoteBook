#ifndef __FACTORY_H__
#define __FACTORY_H__

#include <iostream>
#include <string>
using namespace std;

class FRUIT
{
    public:
        FRUIT(const string &name):_name(name) {}
        ~FRUIT() {}
    
    public:
        virtual string get_name() const;
        string name() const;

    private:
        string _name;
};

class APPLE : public FRUIT
{
    public:
        APPLE(string name):FRUIT(name) {}
        ~APPLE() {}
    
    public:
        string get_name() const;
};

class FACTORY
{
    public:
        virtual FRUIT * build_obj(const string & name) = 0;
};

class APPLE_FACTORY : public FACTORY
{
    public:
        FRUIT * build_obj(const string & name);
};

#endif 