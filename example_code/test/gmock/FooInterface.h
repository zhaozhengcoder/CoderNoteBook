#ifndef FOOINTERFACE_H_
#define FOOINTERFACE_H_

#include <string>

namespace seamless {

class FooInterface {
public:
        virtual ~FooInterface() {}

public:
        virtual std::string get_from_rpc() = 0;

        std::string get_result()
        {
            std::string str = "reuslt is ";
            return str + get_from_rpc();
        }
};

}  // namespace seamless

#endif // FOOINTERFACE_H_