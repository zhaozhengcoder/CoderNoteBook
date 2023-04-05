#include <iostream>
#include <string>
#include <vector>
#include "helper.h"
#include "dep.h"

class MY_SERVICE
{
public:
    int deps_init()
    {
        std::vector<std::string> name =
        {
            "GRPC",
            "GLOG",
        };

        for (int i = 0; i < name.size(); i++)
        {
            COMM_DEPENDENCY* obj = DEPENDENCY_HELPER::inst()->get_by_name(name[i]);
            if (obj)
            {
                // init xxx
            }
        }
        return 0;
    }

    RPC* get_rpc()
    {
        RPC* obj = static_cast<RPC*>(DEPENDENCY_HELPER::inst()->get_by_name("GRPC"));
        return obj;
    }

    LOG* get_log()
    {
        LOG* obj = static_cast<LOG*>(DEPENDENCY_HELPER::inst()->get_by_name("GLOG"));
        return obj;
    }
};

int main()
{
    MY_SERVICE s;
    s.get_rpc()->send("HELLO RPC");
    s.get_log()->print_log("HELLO LOG");
    return 0;
}