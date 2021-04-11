#include "heartbeat.pb.h"
#include <fstream>
#include <assert.h>
#include <iostream>

using namespace std;
using namespace heartbeat;

void traceMsg(const HeartBeatMessage &msg)
{
    cout << msg.datetime() << endl;
    cout << msg.hostname() << endl;
    cout << msg.ip() << endl;
    cout << msg.info() << endl;
    cout << msg.info2() << endl;
    cout << msg.info3() << endl;

    cout <<"========"<<endl;
    cout << msg.DebugString() << endl;
}

int get_feature(const HeartBeatMessage& hb_msg, const std::string& name) 
{
    const google::protobuf::Descriptor* des = hb_msg.GetDescriptor();
    const google::protobuf::FieldDescriptor* fdes = des->FindFieldByName(name);
    assert(fdes != nullptr);
    const google::protobuf::Reflection* ref = hb_msg.GetReflection();
    cout << ref->GetString(hb_msg, fdes) << endl;
    return 0;
}

int main(void)
{
    HeartBeatMessage msg;
        
    fstream input("./heartbeat.db",ios::in|ios::binary);

    if(!msg.ParseFromIstream(&input))
    {
        cerr << "read data from file error." << endl;
        return -1;
    }
    traceMsg(msg);
    get_feature(msg, "hostName");
    return 0;
}