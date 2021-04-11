#include "heartbeat.pb.h"
#include <fstream>
#include <iostream>
#include <sys/time.h>

using namespace std;
using namespace heartbeat;

int main(void){
        HeartBeatMessage msg;
        
        const long dateTime = 100100;
        std::cout << dateTime << std::endl;

        msg.set_datetime(dateTime);
        msg.set_hostname("dataNode-1000");
        msg.set_ip("192.168.0.128");
        msg.set_info("Everything is normal, I'm healthy");
        
        fstream output("./heartbeat.db",ios::out|ios::trunc|ios::binary);
        if (!msg.SerializeToOstream(&output))
        {
                cerr << "save data error." << endl;
                return -1;
        }
        return 0;
}

// protoc   --cpp_out=.   heartbeat.proto 
// export LD_LIBRARY_PATH=/usr/local/lib
// g++ writter.cc heartbeat.pb.cc -lprotobuf -std=c++11 -g -lpthread