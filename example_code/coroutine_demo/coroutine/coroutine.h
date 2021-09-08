#ifndef __COROUTINE_H__
#define __COROUTINE_H__

#include <ucontext.h>
#include <vector>

enum ROUNTINE_STATE {FREE,RUNNABLE,RUNNING,SUSPEND};

typedef void (*TaskFunc)(void *arg);
const int CO_ROUTINE_MAX = 1024 * 100;   // 最多可以运行10w个协程
const int CO_STACK_SIZE  = 1024 * 128;   // 每个协程的大小是128k

const int INVALID_IDX = -1;

class CO_ROUTINE_CTX
{
public:
    ucontext_t ctx;     // 协程的上下文 （协程被切出的时候，上下文保存在这里)
    TaskFunc  func;     // 协程的任务函数
    void *arg;          // 协程任务函数的函数
    enum ROUNTINE_STATE state;     // 协程的状态
    char stack[CO_STACK_SIZE];     // 协程的栈空间
};

class CO_MGR
{
    private:
        CO_MGR();
        static CO_MGR * instance;

    public:
        static CO_MGR * get_instance();
        ucontext_t main;
        int cur_max_num;
        int running_co;
        CO_ROUTINE_CTX co_ctxs[CO_ROUTINE_MAX];
};

int co_create(CO_MGR * mgr, TaskFunc func, void *arg);
int co_yield();
int co_resume(int co_id);
bool co_is_all_finished(CO_MGR * mgr);
bool co_is_dead(CO_MGR * mgr, int co_id);
int get_running_co_id(CO_MGR * mgr);
CO_MGR * co_mgr_get();
#endif