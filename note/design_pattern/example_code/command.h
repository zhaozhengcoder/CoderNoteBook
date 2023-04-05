#ifndef __COMMAND_H__
#define __COMMAND_H__

#include <iostream>
using namespace std;

class Receiver
{
    public:
        void add() {cout << "add" << endl;}
        void multi() {cout << "multi" << endl;}
};

class COMMAND
{
    public:
        virtual void exec() = 0;
};

class ADD_COMMAND : public COMMAND
{
    public:
        ADD_COMMAND(Receiver * r):_r(r) {};
        void exec() {_r->add();};

    private:
        Receiver * _r;
};

class MULT_COMMAND : public COMMAND
{
    public:
        MULT_COMMAND(Receiver * r) : _r(r) {};
        void exec() {_r->multi();};

    private:
        Receiver * _r;
};  

#endif 
