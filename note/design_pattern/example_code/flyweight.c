#include <iostream>
#include <map>

#include "flyweight.h"

using namespace std;

FLYWEIGHT_OBJ* FLYWEIGHT::build_obj(int key)
{
    if (_map.find(key) == _map.end())
    {
        FLYWEIGHT_OBJ * obj = new FLYWEIGHT_OBJ();
        _map[key] = obj;
        return obj;
    }
    else
    {
        return _map[key];
    }
}

int FLYWEIGHT::clear()
{
    map<int, FLYWEIGHT_OBJ *>::iterator iter = _map.begin();
    for (; iter != _map.end(); iter++)
    {
        FLYWEIGHT_OBJ * obj = iter->second;
        delete obj;
    }
    return 0;
}