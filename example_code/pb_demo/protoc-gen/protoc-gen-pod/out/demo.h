#ifndef __DEMO_H_
#define __DEMO_H_

#include <cstdint>
#include "demo.pb.h" 
struct PODUserMsg // pb name UserMsg 
{
	uint32_t id;  //  id = 1 
	uint32_t age;  //  age = 2 
	uint32_t passwd;  //  passwd = 3 

	// method 
	void clear();
	int pb2pod(const UserMsg & pb);
	int pod2pb(UserMsg * pb);
};

struct PODFamilyMsg // pb name FamilyMsg 
{
	PODUserMsg familys[10];
	uint32_t rid_arrs[50];  //  rid_arrs = 2 

	// method 
	void clear();
	int pb2pod(const FamilyMsg & pb);
	int pod2pb(FamilyMsg * pb);
};

#endif
