#include <stdio.h>
#include "coroutine.h"

struct DB_REQ_ARG
{
    int req;
    int result;
};

int send_query_db_req(void * req)
{
    printf("do %s \n", __FUNCTION__);
    return 0;
}

void foo1(void *arg)
{
    DB_REQ_ARG * req = (DB_REQ_ARG *)arg;
    send_query_db_req(req); 

    CO_MGR * mgr = co_mgr_get();
    co_yield();
    printf("func resume, co id %d\n", mgr->running_co);
}

void foo2(void *arg)
{
    DB_REQ_ARG * req = (DB_REQ_ARG *)arg;
    send_query_db_req(req); 

    CO_MGR * mgr = co_mgr_get();
    co_yield();
    printf("func resume once,  co id %d\n", mgr->running_co);
    
    co_yield();
    printf("func resume twice, co id %d\n", mgr->running_co);
}

void schedule_test()
{
    DB_REQ_ARG arg;
    CO_MGR * mgr = co_mgr_get();

    int id1 = co_create(mgr, foo1, &arg);
    if (id1 < 0) {return;}

    int id2 = co_create(mgr, foo2, &arg);
    if (id2 < 0) {return;}

    arg.result = 100;
    while(!co_is_dead(mgr, id1) || !co_is_dead(mgr, id2))
    {
        co_resume(id1);
        co_resume(id2);
    }
    printf("===== %s end ====\n", __FUNCTION__);
}


int main()
{
    schedule_test();

    return 0;
}
