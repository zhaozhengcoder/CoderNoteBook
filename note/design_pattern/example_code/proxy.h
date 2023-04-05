#ifndef __PROYX_H__
#define __PROYX_H__

#include <iostream>
using namespace std;

class REQUEST
{
    public:
        REQUEST() {}
        ~REQUEST() {}

    public:
        int do_requst();
};


class PROXY : public REQUEST
{
    public:
        int do_request_proxy();

        void pre_request() {cout<<"pre"<<endl;}
        void post_request() {cout<<"post"<<endl;}
};

#endif 