#ifndef __DECO_H__
#define __DECO_H__

#include <iostream>
using namespace std;

class Cake
{
public:
    virtual void showCake()=0;
    virtual ~Cake(){};
    std::string name;
};
 
class ConcreteCake :public Cake
{
public:
    ConcreteCake()
    {
        name = "原始蛋糕";
    }
    void showCake(){ std::cout << name.c_str() << std::endl; };
    virtual  ~ConcreteCake(){};
};

class CakeDecrator :public Cake
{
protected:
    Cake* pCake;  //维护一个Cake对象的引用，为Cake对象添加装饰
public:
    virtual void showCake() = 0;
    virtual	~CakeDecrator(){};
};

class CakeDecratorMilk : public CakeDecrator
{
    public:
    CakeDecratorMilk(Cake* pCake)
    {
        this->pCake = pCake;
    }
    void showCake()
    {
        this->name = pCake->name + "加奶油";
        std::cout << name.c_str()<<std::endl;
    };
    virtual ~CakeDecratorMilk(){};
};

#endif 