#ifndef __FLY_WEIGHT_H__
#define __FLY_WEIGHT_H__

#include <iostream>
#include <map>

using namespace std;

class FLYWEIGHT_OBJ
{
    public:
        FLYWEIGHT_OBJ():_data(0) {cout << "create obj" <<endl;}
    private:
        int _data;
};

class FLYWEIGHT
{
    public:
        FLYWEIGHT_OBJ * build_obj(int key);
        int clear();

    private:
        std::map<int, FLYWEIGHT_OBJ *> _map;
};

#endif