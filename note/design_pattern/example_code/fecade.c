#include <iostream>
#include "fecade.h"

FECADE_OBJ* FECADE::build_obj()
{
    FECADE_OBJ * obj = new FECADE_OBJ();

    // 1. step 1
    obj->set_name();

    // 2. step 2
    obj->set_attr();

    // 3. step 3
    obj->set_info();

    return obj;
}