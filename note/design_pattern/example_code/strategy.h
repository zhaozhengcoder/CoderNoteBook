#ifndef __STRATEGY_H__
#define __STRATEGY_H__

class TAX
{
    public:
        TAX(){}
        ~TAX(){}
    public:
        virtual int cal_tax();
};

class CHINA_TAX : public TAX
{
    public:
        CHINA_TAX(){}
        ~CHINA_TAX(){}

    public:
        virtual int cal_tax();
};


#endif