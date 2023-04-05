#include <iostream>
#include "template.h"

using namespace std;

int FRAMEWORK::init()
{
    cout << "frame work init" << endl;
    return 0;
}

int FRAMEWORK::load()
{
    cout << "frame work load" << endl;
    return 0;
}

int FRAMEWORK::work()
{
    cout << "frame work work" << endl;
    return 0;
}

int FRAMEWORK::fini()
{
    cout << "frame work fini" << endl;
    return 0;
}

// BUSINESS
int BUSINESS::init()
{
    cout << "business work init" << endl;
    return 0;
}

int BUSINESS::load()
{
    cout << "business work load" << endl;
    return 0;
}

int BUSINESS::work()
{
    cout << "business work work" << endl;
    return 0;
}

int BUSINESS::fini()
{
    cout << "business work fini" << endl;
    return 0;
}
