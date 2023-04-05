#ifndef __HEARTBEAT_H_
#define __HEARTBEAT_H_

#include <cstdint>
#include "heartbeat.pb.h" 
struct PODHeartBeatReqMessage // pb name HeartBeatReqMessage 
{
	uint32_t trace_id;  //  trace_id = 1 
	uint32_t ip;  //  ip = 2 
	uint32_t time;  //  time = 3 
	HeartBeatReqMessage::MachineEnum type;  // EnumValues{{Name: E_PC}, {Name: E_IOS, Number: 1}, {Name: E_ANDRIOD, Number: 2}}  

	// method 
	void clear();
	int pb2pod(const HeartBeatReqMessage & pb);
	int pod2pb(HeartBeatReqMessage * pb);
};

struct PODHeartBeatRspMessage // pb name HeartBeatRspMessage 
{
	uint32_t trace_id;  //  trace_id = 1 
	uint32_t ret;  //  ret = 2 

	// method 
	void clear();
	int pb2pod(const HeartBeatRspMessage & pb);
	int pod2pb(HeartBeatRspMessage * pb);
};

#endif
