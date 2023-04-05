#include "heartbeat.h" 
#include "heartbeat.pb.h" 

// method 
void PODHeartBeatReqMessage::clear()
{
	trace_id = 0; 
	ip = 0; 
	time = 0; 
	type = HeartBeatReqMessage::E_PC; 
}

int PODHeartBeatReqMessage::pb2pod(const HeartBeatReqMessage & pb)
{
		trace_id = pb.trace_id(); 
		ip = pb.ip(); 
		time = pb.time(); 
		type = pb.type(); 
	return 0;
}

int PODHeartBeatReqMessage::pod2pb(HeartBeatReqMessage * pb)
{
	pb->set_trace_id(trace_id); 
	pb->set_ip(ip); 
	pb->set_time(time); 
	pb->set_type(type); 
	return 0;
}


// method 
void PODHeartBeatRspMessage::clear()
{
	trace_id = 0; 
	ret = 0; 
}

int PODHeartBeatRspMessage::pb2pod(const HeartBeatRspMessage & pb)
{
		trace_id = pb.trace_id(); 
		ret = pb.ret(); 
	return 0;
}

int PODHeartBeatRspMessage::pod2pb(HeartBeatRspMessage * pb)
{
	pb->set_trace_id(trace_id); 
	pb->set_ret(ret); 
	return 0;
}

