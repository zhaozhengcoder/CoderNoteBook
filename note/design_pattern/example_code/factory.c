#include <iostream>
#include <string>
using namespace std;

#include "factory.h"

string FRUIT::get_name() const 
{
    return _name;
}
string FRUIT::name() const
{
    return _name;
}

string APPLE::get_name() const 
{
    string tmp = "apple + : " + name();
    return tmp;
}

FRUIT* APPLE_FACTORY::build_obj(const string & name)
{
    FRUIT * fruit = new APPLE(name);
    cout << fruit->get_name() << endl;
    return fruit;
}