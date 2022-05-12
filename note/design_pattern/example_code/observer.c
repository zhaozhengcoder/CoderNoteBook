#include <iostream>
#include <vector>

#include "observer.h"
using namespace std;

int TOPIC::notfiy()
{
    cout << "TOPIC::notfiy" << endl;
    return 0;
}

int NEWS::notfiy()
{
    cout << "TOPIC::notfiy" << endl;
    return 0;
}

int MUSIC::notfiy()
{
    cout << "TOPIC::notfiy" << endl;
    return 0;
}
