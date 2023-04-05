#ifndef __TEMPLATE_H__
#define __TEMPLATE_H__


class FRAMEWORK
{
    public:
        FRAMEWORK() {}
        ~FRAMEWORK(){}

    public:
        virtual int init();
        virtual int load();
        virtual int work();
        virtual int fini();
};

class BUSINESS : public FRAMEWORK
{
    public:
        BUSINESS() {}
        ~BUSINESS(){}

    public:
        virtual int init();
        virtual int load();
        virtual int work();
        virtual int fini();
};

#endif