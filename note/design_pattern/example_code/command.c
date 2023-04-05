#include "command.h"
#include <iostream>

int func()
{
    Receiver r;
    ADD_COMMAND  c1(&r);
    MULT_COMMAND c2(&r);

    c1.exec();
    c2.exec();
    return 0;
}