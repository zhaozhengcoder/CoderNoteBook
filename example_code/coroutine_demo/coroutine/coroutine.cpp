#include <stdio.h>
#include <ucontext.h>
#include <vector>
#include "coroutine.h"

CO_MGR* CO_MGR::instance = NULL; 
void co_swap_func(CO_MGR *mgr);

CO_MGR::CO_MGR():running_co(INVALID_IDX),cur_max_num(0)
{
    for (int i = 0; i < CO_ROUTINE_MAX; i++)
    {
        co_ctxs[i].state = FREE;
    }            
}

CO_MGR * CO_MGR::get_instance()
{
    if (instance == NULL)
    {
        instance = new CO_MGR();
        return instance;
    }
    return instance;
}

int co_create(CO_MGR * mgr, TaskFunc func, void *arg)
{
    int co_idx = INVALID_IDX;
    for (int i = 0; i < mgr->cur_max_num; i++)
    {
        if (mgr->co_ctxs[i].state == FREE)
        {
            co_idx = i;
        }
    }

    if (co_idx == INVALID_IDX)
    {
        if (mgr->cur_max_num == CO_ROUTINE_MAX)
        {
            printf("coroutine num excced max, max is %d", CO_ROUTINE_MAX);
            return -1;
        }

        co_idx = mgr->cur_max_num;
        mgr->cur_max_num++;
    }

    CO_ROUTINE_CTX* co = &mgr->co_ctxs[co_idx];
    co->state = RUNNABLE;
    co->func = func;
    co->arg = arg;
    getcontext(&(co->ctx));
    co->ctx.uc_stack.ss_sp = co->stack;
    co->ctx.uc_stack.ss_size = CO_STACK_SIZE;
    co->ctx.uc_stack.ss_flags = 0;
    co->ctx.uc_link = &(mgr->main);

    mgr->running_co = co_idx;
    
    makecontext(&(co->ctx),(void (*)(void))(co_swap_func), 1, mgr);
    swapcontext(&(mgr->main), &(co->ctx));
    return co_idx;
}

int co_resume(int co_id)
{
    CO_MGR * mgr = co_mgr_get();
    CO_ROUTINE_CTX* co = &mgr->co_ctxs[co_id];
    if (co->state == SUSPEND)
    {
        int bak_id = mgr->running_co;
        mgr->running_co = co_id;
        co->state = RUNNING;
        printf("resume switch co %d to %d \n", bak_id, co_id);
        swapcontext(&(mgr->main), &(co->ctx));
    }
    return 0;
}

int co_yield()
{
    CO_MGR * mgr = co_mgr_get();

    int bak = mgr->running_co;
    CO_ROUTINE_CTX* co = &mgr->co_ctxs[mgr->running_co];
    co->state = SUSPEND;
    mgr->running_co = -1;
    printf("yield switch co %d to %d \n", bak, mgr->running_co);

    swapcontext(&(co->ctx), &(mgr->main));
    return 0;
}

void co_swap_func(CO_MGR *mgr)
{
    if (mgr == NULL) {return;}

    if (mgr->running_co != -1)
    {
        CO_ROUTINE_CTX* co = &mgr->co_ctxs[mgr->running_co];
        co->func(co->arg);
    
        co->state = FREE;
        
        // uclink 指定切换到main，所以当此函数执行完毕就会切换到main
        mgr->running_co = -1;
    }
    return;
}

bool co_is_all_finished(CO_MGR * mgr)
{
    if (mgr == NULL) {return false;}

    for (int i = 0; i < mgr->cur_max_num; i++)
    {
        if (mgr->co_ctxs[i].state != FREE)
        {
            return false;
        }
    }
    return true;
}

bool co_is_dead(CO_MGR * mgr, int co_id)
{
    if (mgr == NULL) {return true;}

    if (mgr->co_ctxs[co_id].state == FREE)
    {
        return true;
    }
    return false;
}

int get_running_co_id(CO_MGR * mgr)
{
    if (mgr == NULL) {return -1;}
    return mgr->running_co;
}

CO_MGR * co_mgr_get()
{
    CO_MGR * mgr = CO_MGR::get_instance();
    return mgr;
}