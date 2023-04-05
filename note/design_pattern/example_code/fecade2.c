#include <iostream>
#include "fecade2.h"

FECADE2* FECADE2::build_obj()
{
    FECADE2 * obj = new FECADE2();

    // 1. step 1
    obj->set_name();

    // 2. step 2
    obj->set_attr();

    // 3. step 3
    obj->set_info();

    return obj;
}