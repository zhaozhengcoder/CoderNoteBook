#include <iostream>
#include "singleton.h"
#include "template.h"
#include "factory.h"
#include "flyweight.h"
#include "fecade.h"
#include "fecade2.h"
#include "proxy.h"

using namespace std;

int main()
{
    cout << "main" << endl;
    
    SINGLETON * instance  = SINGLETON::get_instance();
    if (instance != NULL)
    {
        cout << "get instance" << endl;
    }

    FRAMEWORK * business = new BUSINESS();
    business->init();
    business->load();
    business->work();
    business->fini();

    FACTORY * f = new APPLE_FACTORY();
    f->build_obj("hahah");

    FLYWEIGHT mgr;
    int key1 = 100;
    FLYWEIGHT_OBJ * obj1 = mgr.build_obj(key1);
    FLYWEIGHT_OBJ * obj2 = mgr.build_obj(key1);

    // FECADE fecade;
    // fecade.build_obj();

    FECADE2 f2;
    f2.build_obj();
    
    PROXY proxy;
    proxy.do_request_proxy();

    return 0;
}