#ifndef __FECADE2_H__
#define __FECADE2_H__

#include <iostream>
using namespace std;

class FECADE2
{
    public:
        void set_name() {cout << "set name" << endl;}
        void set_attr() {cout << "set attr" << endl;}
        void set_info() {cout << "set info" << endl;}

    public:
        static FECADE2* build_obj();

    public:
        int _data;
};


#endif 