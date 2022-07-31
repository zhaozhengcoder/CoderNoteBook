#include <iostream>
#include <sstream>
#include <map>
#include <queue>
#include "person.pb.h"

using namespace std;

int pb_fill_message(std::queue<std::string>& args, google::protobuf::Message* msg);

int print_pb_message(const google::protobuf::Message & message)
{
    const google::protobuf::Descriptor* pDescriptor = message.GetDescriptor();
    int count = pDescriptor->field_count();
    cout << "field count : " << count << "  message : " 
         << pDescriptor->name() << " file desc" << pDescriptor->file()<< endl;

    for (int i = 0; i < count; i++)
    {
        const google::protobuf::FieldDescriptor * pFieldDesc = pDescriptor->field(i);
        cout << "field index : " << i << ", field name :" << pFieldDesc->name() 
             << ", field type : " << pFieldDesc->cpp_type() << ", is repeated : " 
             << pFieldDesc->is_repeated() << ", number : " << pFieldDesc->number()  << endl;

        // option
        pFieldDesc->options();
    }
    cout << message.DebugString() << endl;
    return 0;
}

// reflect
int fill_pb_message(google::protobuf::Message & message)
{
    const google::protobuf::Reflection* pReflection = message.GetReflection();

    const google::protobuf::Descriptor* pDescriptor = message.GetDescriptor();
    int count = pDescriptor->field_count();

    for (int i = 0; i < count; i++)
    {
        const google::protobuf::FieldDescriptor * field = pDescriptor->field(i);
        bool has_field = pReflection->HasField(message, field);
        if (has_field)
        {
            if (field->cpp_type() == google::protobuf::FieldDescriptor::CPPTYPE_UINT32)
            {
                cout << pReflection->GetUInt32(message, field) << endl;

                // 利用反射填充对象
                int field_value = 666;
                pReflection->SetUInt32(&message, field, field_value);
            }
        }
    }
    return 0;
}

int PbToMap(const google::protobuf::Message &message,
            std::map<std::string, std::string> &out) 
{
    #define CASE_FIELD_TYPE(cpptype, method, valuetype)                            \
    case google::protobuf::FieldDescriptor::CPPTYPE_##cpptype: {                   \
        valuetype value = reflection->Get##method(message, field);                 \
        std::ostringstream oss;                                                    \
        oss << value;                                                              \
        out[field->name()] = oss.str();                                            \
        break;                                                                     \
    }

    #define CASE_FIELD_TYPE_ENUM()                                                 \
    case google::protobuf::FieldDescriptor::CPPTYPE_ENUM: {                        \
        int value = reflection->GetEnum(message, field)->number();                 \
        std::ostringstream oss;                                                    \
        oss << value;                                                              \
        out[field->name()] = oss.str();                                            \
        break;                                                                     \
    }

    #define CASE_FIELD_TYPE_STRING()                                               \
    case google::protobuf::FieldDescriptor::CPPTYPE_STRING: {                      \
        std::string value = reflection->GetString(message, field);                 \
        out[field->name()] = value;                                                \
        break;                                                                     \
    }

    const google::protobuf::Descriptor *descriptor = message.GetDescriptor();
    const google::protobuf::Reflection *reflection = message.GetReflection();

    for (int i = 0; i < descriptor->field_count(); i++) 
    {
        const google::protobuf::FieldDescriptor *field = descriptor->field(i);
        bool has_field = reflection->HasField(message, field);

        if (has_field) 
        {
            if (field->is_repeated()) 
            {
                return -1; // 不支持转换repeated字段
            }

            const std::string &field_name = field->name();
            switch (field->cpp_type()) 
            {
                CASE_FIELD_TYPE(INT32, Int32, int);
                CASE_FIELD_TYPE(UINT32, UInt32, uint32_t);
                CASE_FIELD_TYPE(FLOAT, Float, float);
                CASE_FIELD_TYPE(DOUBLE, Double, double);
                CASE_FIELD_TYPE(BOOL, Bool, bool);
                CASE_FIELD_TYPE(INT64, Int64, int64_t);
                CASE_FIELD_TYPE(UINT64, UInt64, uint64_t);
                CASE_FIELD_TYPE_ENUM();
                CASE_FIELD_TYPE_STRING();
            default:
                return -1; // 其他异常类型
            }
        }
    }
    return 0;
} 

int pb_fill_field(std::queue<std::string>& args
        , google::protobuf::Message* msg
        , const google::protobuf::FieldDescriptor* field_des)
{
    if (args.empty())
    {
        std::string err_ret = field_des->full_name() + "failed";
        args.push(err_ret);
        return -1;
    }

    const google::protobuf::Reflection* msg_ref = msg->GetReflection();
    assert(msg_ref != NULL);

    const char* cur_arg = args.front().c_str();
    switch (field_des->cpp_type())
    {
        case google::protobuf::FieldDescriptor::CPPTYPE_STRING:
            {
                msg_ref->SetString(msg, field_des, cur_arg);
                args.pop();
                break;
            }
        case google::protobuf::FieldDescriptor::CPPTYPE_INT32:
            {
                int value = atoi(cur_arg);
                msg_ref->SetInt32(msg, field_des, value);
                args.pop();
                break;
            }
        case google::protobuf::FieldDescriptor::CPPTYPE_BOOL:
            {
                bool value = (bool)atoi(cur_arg);
                msg_ref->SetBool(msg, field_des, value);
                args.pop();
                break;
            }
        case google::protobuf::FieldDescriptor::CPPTYPE_FLOAT:
            {
                float value = (float)atof(cur_arg);
                msg_ref->SetFloat(msg, field_des, value);
                args.pop();
                break;
            }
        case google::protobuf::FieldDescriptor::CPPTYPE_DOUBLE:
            {
                double value = atof(cur_arg);
                msg_ref->SetDouble(msg, field_des, value);
                args.pop();
                break;
            }
        case google::protobuf::FieldDescriptor::CPPTYPE_UINT64:
            {
                unsigned long int value = strtoull(cur_arg, NULL, 10);;
                msg_ref->SetUInt64(msg, field_des, value);
                args.pop();
                break;
            }
        case google::protobuf::FieldDescriptor::CPPTYPE_INT64:
            {
                long int value = strtoll(cur_arg, NULL, 10);
                msg_ref->SetInt64(msg, field_des, value);
                args.pop();
                break;
            }
        case google::protobuf::FieldDescriptor::CPPTYPE_UINT32:
            {
                unsigned int value = (unsigned int)atoi(cur_arg);;
                msg_ref->SetUInt32(msg, field_des, value);
                args.pop();
                break;
            }
        case google::protobuf::FieldDescriptor::CPPTYPE_MESSAGE:
            {
                google::protobuf::Message* pMsg = msg_ref->MutableMessage(msg, field_des);
                return pb_fill_message(args, pMsg);
            }
        default:
            {
                std::string err_ret = field_des->full_name() + " failed";
                args.push(err_ret);
                return -1;
            }
    }
    return 0;
}

int pb_fill_repeated_field(std::queue<std::string>& args
    , google::protobuf::Message* msg
    , const google::protobuf::FieldDescriptor* field_des
    , int32_t nFieldIndex)
{
    if (args.empty())
    {
        std::string err_ret = field_des->full_name() + "repeated failed";
        args.push(err_ret);
        return -1;
    }

    const google::protobuf::Reflection* msg_ref = msg->GetReflection();
    if (msg_ref == NULL) {return -1;}

    const char* cur_arg = args.front().c_str();
    switch (field_des->cpp_type())
    {
        case google::protobuf::FieldDescriptor::CPPTYPE_MESSAGE:
            {
                google::protobuf::Message* pSubMessage = msg_ref->AddMessage(msg, field_des);
                assert(pSubMessage != NULL);

                return pb_fill_message(args, pSubMessage);
            }
        case google::protobuf::FieldDescriptor::CPPTYPE_STRING:
            {
                msg_ref->SetString(msg, field_des, cur_arg);
                args.pop();
                break;
            }
        case google::protobuf::FieldDescriptor::CPPTYPE_INT32:
            {
                int value = atoi(cur_arg);
                msg_ref->AddInt32(msg, field_des, value);
                args.pop();
                break;
            }
        case google::protobuf::FieldDescriptor::CPPTYPE_INT64:
            {
                long int value = strtoll(cur_arg, NULL, 10);
                msg_ref->AddInt64(msg, field_des, value);
                args.pop();
                break;
            }
        case google::protobuf::FieldDescriptor::CPPTYPE_BOOL:
            {
                bool value = (bool)atoi(cur_arg);
                msg_ref->AddBool(msg, field_des, value);
                args.pop();
                break;
            }
        case google::protobuf::FieldDescriptor::CPPTYPE_FLOAT:
            {
                float value = (float)atof(cur_arg);
                msg_ref->AddFloat(msg, field_des, value);
                args.pop();
                break;
            }
        case google::protobuf::FieldDescriptor::CPPTYPE_DOUBLE:
            {
                double value = atof(cur_arg);
                msg_ref->AddDouble(msg, field_des, value);
                args.pop();
                break;
            }
        case google::protobuf::FieldDescriptor::CPPTYPE_UINT32:
            {
                unsigned int value = (unsigned int)atoi(cur_arg);;
                msg_ref->AddUInt32(msg, field_des, value);
                args.pop();
                break;
            }
        case google::protobuf::FieldDescriptor::CPPTYPE_UINT64:
            {
                unsigned long int value = strtoull(cur_arg, NULL, 10);;
                msg_ref->AddUInt64(msg, field_des, value);
                args.pop();
                break;
            }
        default:
            {
                std::string err_ret = field_des->full_name() + " repeared failed";
                args.push(err_ret);
                return -1;
            }
            break;
    }
    return 0;
}

int pb_fill_message(std::queue<std::string>& args, google::protobuf::Message* msg)
{
    const google::protobuf::FieldDescriptor* field_des = NULL;
    const google::protobuf::Descriptor* descriptor = msg->GetDescriptor();
    const google::protobuf::Reflection* msg_ref = msg->GetReflection();

    int ret = 0;
    for (int32_t i = 0; i < descriptor->field_count(); ++i)
    {
        field_des = descriptor->field(i);
        if (args.empty())
        {
            std::string err_ret = field_des->full_name() + " failed";
            args.push(err_ret);
            return -1;
        }

        const char* cur_arg = args.front().c_str();
        if (field_des->is_repeated())
        {
            int32_t nArraySize = atoi(cur_arg);
            args.pop();

            for (int32_t i = 0; i < nArraySize; i++)
            {
                ret = pb_fill_repeated_field(args, msg, field_des, i);
                if (ret != 0) return ret;
            }
        }
        else
        {
            ret = pb_fill_field(args, msg, field_des);
            if (ret != 0) return ret;
        }
    }
    return 0;
}

google::protobuf::Message* pb_create_by_name(const char *type_name)
{
    google::protobuf::Message* message = NULL;

    const google::protobuf::Descriptor* descriptor =
        google::protobuf::DescriptorPool::generated_pool()->FindMessageTypeByName(type_name);
    if (descriptor)
    {
        google::protobuf::MessageFactory* factory = 
            google::protobuf::MessageFactory::generated_factory();
        assert(factory != NULL);
        
        const google::protobuf::Message* prototype = factory->GetPrototype(descriptor);
        if (prototype)
        {
            message = prototype->New();
        }
    }
    return message;
}

int string_to_pb()
{
    google::protobuf::Message* message = pb_create_by_name("PersonInfo");

    std::queue<std::string> args;
    args.push("10001");
    args.push("18");
    args.push("123456");
    args.push("haha");

    int ret = pb_fill_message(args, message);
    if (ret != 0) {
        cout << "fill failed" << endl;
        return ret;
    }
    cout << "string_to_pb >>>> " << message->DebugString() << endl;
    return 0;
}

int main()
{
    PersonInfo info;
    info.set_age(100);
    cout <<"debug string : " << info.DebugString() << endl;

    print_pb_message(info);
    fill_pb_message(info);
    cout <<"debug string : " << info.DebugString() << endl;

    std::map<std::string,std::string> pb_map;
    PbToMap(info, pb_map);

    int ret = string_to_pb();

    // Student oStudent1;
    // oStudent1.set_name("xiao");

    // Student oStudent2;
    // oStudent2.set_name("xiaowei");

    // allCheck(oStudent1);
    // allCheck(oStudent2);

    return ret;
}

// https://cloud.tencent.com/developer/article/1753977
// https://blog.csdn.net/JMW1407/article/details/107223287
