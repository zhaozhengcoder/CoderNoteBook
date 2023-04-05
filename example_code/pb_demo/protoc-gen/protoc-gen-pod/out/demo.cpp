#include "demo.h" 
#include "demo.pb.h" 

// method 
void PODUserMsg::clear()
{
	id = 0; 
	age = 0; 
	passwd = 0; 
}

int PODUserMsg::pb2pod(const UserMsg & pb)
{
		id = pb.id(); 
		age = pb.age(); 
		passwd = pb.passwd(); 
	return 0;
}

int PODUserMsg::pod2pb(UserMsg * pb)
{
	pb->set_id(id); 
	pb->set_age(age); 
	pb->set_passwd(passwd); 
	return 0;
}


// method 
void PODFamilyMsg::clear()
{
	for (int i = 0; i < 10; i++) {
	familys[i].clear(); 
	}
	for (int i = 0; i < 50; i++) {
	rid_arrs[i] = 0; 
	}
}

int PODFamilyMsg::pb2pod(const FamilyMsg & pb)
{
	for (int i = 0; i < 10; i++) {
		familys[i].pb2pod(pb.familys(i)); 
	}
	for (int i = 0; i < 50; i++) {
		rid_arrs[i] = pb.rid_arrs(i); 
	}
	return 0;
}

int PODFamilyMsg::pod2pb(FamilyMsg * pb)
{
	for (int i = 0; i < 10; i++) {
	familys[i].pod2pb(pb->add_familys()); 
	}
	for (int i = 0; i < 50; i++) {
	pb->add_rid_arrs(rid_arrs[i]); 
	}
	return 0;
}

