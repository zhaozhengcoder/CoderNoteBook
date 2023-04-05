#include <atomic>
#include <unistd.h>
#include <cstddef>
#include <iostream>
#include <thread> 
#include <mutex>
#include <assert.h>
#include "../../lockfree_stack.h"

using namespace std; 
const int TASK_REPEATED_TIMES = 10;
const int THREAD_NUM = 4;

Stack stack;

int stack_push(int val,int thread_info)
{
    stack.push(val, thread_info);
    // printf("thread id : %lu, push_val %d , info %d\n"
    //     , std::this_thread::get_id(), val, thread_info);
    return 0;
}

int stack_pop()
{
    Node * node = stack.pop();
    if (node == NULL)
    {
        printf("thread id : %lu, empty \n", std::this_thread::get_id());
        return 0;
    }
    // printf("thread id : %d, pop %d \n"
    //         , std::this_thread::get_id(), node->val);
    // stack.print();
    return 0;
}

void task_push(int thread_id) 
{
    for (int i = 0; i < TASK_REPEATED_TIMES; i++)
    {
        stack_push(i, thread_id);
    }
}

void task_pop()
{
    for (int i = 0; i < TASK_REPEATED_TIMES; i++)
    {
        stack_pop();
    }
}

void unit_test_push()
{
    thread thead_arr[THREAD_NUM];
    for (int i = 0; i < THREAD_NUM; i++)
    {
        int thread_info = i * 1000;
        thead_arr[i] = thread(task_push, thread_info);
    }

    for (int i = 0; i < THREAD_NUM; i++)
    {
        thead_arr[i].join();
    }

    assert(stack.get_size() == THREAD_NUM * TASK_REPEATED_TIMES);
    return;
}

void unit_test_pop()
{
    assert(stack.get_size() == THREAD_NUM * TASK_REPEATED_TIMES);

    thread thead_arr[THREAD_NUM];
    for (int i = 0; i < THREAD_NUM; i++)
    {
        thead_arr[i] = thread(task_pop);
    }

    for (int i = 0; i < THREAD_NUM; i++)
    {
        thead_arr[i].join();
    }
    assert(stack.get_size() == 0);
    return;
}

void unit_test_mix()
{
    printf("stack size %d", stack.get_size());
    const int push_thread_num = 20;
    const int pop_thread_num = 10;

    thread thead_push[push_thread_num];
    for (int i = 0; i < push_thread_num; i++)
    {
        int thread_info = i * 1000;
        thead_push[i] = thread(task_push, thread_info);
    }

    thread thead_pop[pop_thread_num];
    for (int i = 0; i < pop_thread_num; i++)
    {
        thead_pop[i] = thread(task_pop);
    }

    // join
    for (int i = 0; i < push_thread_num; i++)
    {
        thead_push[i].join();
    }
    for (int i = 0; i < pop_thread_num; i++)
    {
        thead_pop[i].join();
    }

    printf("stack size %d", stack.get_size());
    return;
}

int main()
{
    unit_test_push();
    stack.print();

    unit_test_pop();
    stack.print();
    
    unit_test_mix();
    return 0;
}