#ifndef MOCKFOO_H_
#define MOCKFOO_H_

#include <gmock/gmock.h>
#include <string>
#include "FooInterface.h"

namespace seamless {

class MockFoo: public FooInterface 
{
    public:
        MOCK_METHOD0(get_from_rpc, std::string());
};

}  // namespace seamless

#endif // MOCKFOO_H_