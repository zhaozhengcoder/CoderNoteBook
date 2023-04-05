#pragma once

#include <map>
#include <string>

class COMM_DEPENDENCY;

class DEPENDENCY_HELPER
{
private:
    std::map<std::string, COMM_DEPENDENCY *> _map_str2obj;
    static DEPENDENCY_HELPER* helper;
    DEPENDENCY_HELPER() {}

public:
    static DEPENDENCY_HELPER* inst()
    {
        if (!helper)
        {
            helper = new DEPENDENCY_HELPER();
        }
        return helper;
    }

    COMM_DEPENDENCY* get_by_name(std::string name)
    {
        if (_map_str2obj.find(name) != _map_str2obj.end())
        {
            return _map_str2obj[name];
        }
        return nullptr;
    }

    void push(std::string name, COMM_DEPENDENCY * obj) 
    { 
        _map_str2obj[name] = obj; 
    }
};

DEPENDENCY_HELPER* DEPENDENCY_HELPER::helper = nullptr;

#define REGISTER(CLASS_TYPE) \
    class CLASS_TYPE##Generator {\
        public:\
            CLASS_TYPE##Generator() {\
                DEPENDENCY_HELPER::inst()->push(#CLASS_TYPE, new CLASS_TYPE());\
            }\
    };\
    CLASS_TYPE##Generator* CLASS_TYPE##Inst = new CLASS_TYPE##Generator();
