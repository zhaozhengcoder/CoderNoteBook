#ifndef __MACHINE_H_
#define __MACHINE_H_

#include <cstdint>
#include "machine.pb.h" 
struct PODInfoMessage // pb name InfoMessage 
{
	uint32_t ip;  //  ip = 1 
	uint32_t time;  //  time = 2 

	// method 
	void clear();
	int pb2pod(const InfoMessage & pb);
	int pod2pb(InfoMessage * pb);
};

struct PODMachineInfoMessage // pb name MachineInfoMessage 
{
	uint32_t trace_id;  //  trace_id = 1 
	PODInfoMessage info;
	uint32_t type;  //  type = 3 

	// method 
	void clear();
	int pb2pod(const MachineInfoMessage & pb);
	int pod2pb(MachineInfoMessage * pb);
};

#endif
