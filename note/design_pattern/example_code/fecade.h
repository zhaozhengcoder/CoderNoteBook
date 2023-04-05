#ifndef __FECADE_H__
#define __FECADE_H__

#include <iostream>
using namespace std;

class FECADE_OBJ
{
    public:
        int _data;

    public:
        void set_name() {cout << "set name" << endl;}
        void set_attr() {cout << "set attr" << endl;}
        void set_info() {cout << "set info" << endl;}
};

class FECADE
{
    public:
        FECADE_OBJ* build_obj();
};


#endif 