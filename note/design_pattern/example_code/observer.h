#ifndef __OBSERVER_H__
#define __OBSERVER_H__

#include <iostream>
#include <vector>

class TOPIC
{
    public:
        TOPIC() {}
        ~TOPIC() {}

    public:
        virtual int notfiy();
};

class NEWS : public TOPIC
{
    public:
        NEWS() {}
        ~NEWS() {}

    public:
        virtual int notfiy();
};

class MUSIC : public TOPIC
{
    public:
        MUSIC(){}
        ~MUSIC(){}

    public:
        virtual int notfiy();
};

class OBSERVER
{
    public:
        OBSERVER() {}
        ~OBSERVER() {}

    public:
        int add(TOPIC*) {return 0;}
        int rm(TOPIC*) {return 0;}

    private:
        std::vector<TOPIC*> topic_vec;
};

#endif 