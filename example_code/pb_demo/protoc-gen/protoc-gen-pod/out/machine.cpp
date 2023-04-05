#include "machine.h" 
#include "machine.pb.h" 

// method 
void PODInfoMessage::clear()
{
	ip = 0; 
	time = 0; 
}

int PODInfoMessage::pb2pod(const InfoMessage & pb)
{
		ip = pb.ip(); 
		time = pb.time(); 
	return 0;
}

int PODInfoMessage::pod2pb(InfoMessage * pb)
{
	pb->set_ip(ip); 
	pb->set_time(time); 
	return 0;
}


// method 
void PODMachineInfoMessage::clear()
{
	trace_id = 0; 
	info.clear(); 
	type = 0; 
}

int PODMachineInfoMessage::pb2pod(const MachineInfoMessage & pb)
{
		trace_id = pb.trace_id(); 
		info.pb2pod(pb.info()); 
		type = pb.type(); 
	return 0;
}

int PODMachineInfoMessage::pod2pb(MachineInfoMessage * pb)
{
	pb->set_trace_id(trace_id); 
	info.pod2pb(pb->mutable_info()); 
	pb->set_type(type); 
	return 0;
}

