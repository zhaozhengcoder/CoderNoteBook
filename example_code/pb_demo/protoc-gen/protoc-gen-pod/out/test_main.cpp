#include <iostream>
#include <assert.h>
#include "demo.pb.h"
#include "demo.h"
#include "heartbeat.h"
#include "heartbeat.pb.h"
#include "machine.h"

using namespace std;

int main()
{
    {
        UserMsg pb;
        PODUserMsg pod;
        pod.clear();
        pod.id = 1;
        pod.age = 2;

        pod.pod2pb(&pb);
        assert(pb.id() == pod.id);
        assert(pb.age() == pod.age);

        pod.clear();
        pod.pb2pod(pb);
        assert(pb.id() == pod.id);
        assert(pb.age() == pod.age);
    }

    {
        PODHeartBeatReqMessage pod;
        HeartBeatReqMessage    pb;
        pod.clear();
        pod.trace_id = 123;
        pod.ip = 456;
        pod.time = 789;
        pod.type = HeartBeatReqMessage_MachineEnum::HeartBeatReqMessage_MachineEnum_E_IOS;

        pod.pod2pb(&pb);
        assert(pb.trace_id() == pod.trace_id);
        assert(pb.ip() == pod.ip);
        assert(pb.time() == pod.time);
        assert(pb.type() == pod.type);

        pod.clear();
        pod.pb2pod(pb);
        assert(pb.trace_id() == pod.trace_id);
        assert(pb.ip() == pod.ip);
        assert(pb.time() == pod.time);
        assert(pb.type() == pod.type);
    }

    {
        PODMachineInfoMessage pod;
        MachineInfoMessage pb;
        pod.clear();
        pod.trace_id = 123;
        pod.info.ip = 456;
        pod.info.time = 789;
        pod.type = 1000;

        pod.pod2pb(&pb);
        assert(pb.trace_id() == pod.trace_id);
        assert(pb.info().ip() == pod.info.ip);
        assert(pb.info().time() == pod.info.time);
        assert(pb.type() == pod.type);
    }

    {
        PODFamilyMsg pod;
        FamilyMsg pb;
        pod.clear();
        pod.familys[0].id = 100;
        pod.familys[0].age = 123;
        pod.familys[1].id = 200;
        pod.familys[2].age = 456;

        // rt to pb
        pod.pod2pb(&pb);
        assert(pb.familys(0).age() == pod.familys[0].age);
        assert(pb.familys(0).id() == pod.familys[0].id);
        assert(pb.familys(1).age() == pod.familys[1].age);
        assert(pb.familys(1).id() == pod.familys[1].id);

        // pb to rt
        pod.clear();
        pod.pb2pod(pb);
        assert(pb.familys(0).age() == pod.familys[0].age);
        assert(pb.familys(0).id() == pod.familys[0].id);
        assert(pb.familys(1).age() == pod.familys[1].age);
        assert(pb.familys(1).id() == pod.familys[1].id);
    }
    cout << "pass" <<endl;
    return 0;
}