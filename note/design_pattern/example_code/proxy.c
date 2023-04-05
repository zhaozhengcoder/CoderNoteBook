#include <iostream>
#include "proxy.h"
using namespace std;

int REQUEST::do_requst()
{
    cout << "do request" << endl;
    return 0;
}

int PROXY::do_request_proxy()
{
    pre_request();
    do_requst();
    post_request();
    return 0;
}