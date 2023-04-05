#include <cstddef>
#include "singleton.h"

SINGLETON * SINGLETON::_instance = get_instance();

SINGLETON* SINGLETON::get_instance()
{
    if (_instance == NULL)
    {
        LOCK guard;
        if (_instance == NULL)
        {
            _instance = new SINGLETON();
        }
    }
    return _instance;
}