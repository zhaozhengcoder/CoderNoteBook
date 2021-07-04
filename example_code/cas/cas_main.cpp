#include <atomic>
#include <cstddef>
#include <iostream>
#include <thread> 
#include <mutex>
#include "cas.h"

using namespace std; 
const int TASK_REPEATED_TIMES = 5;
const int THREAD_NUM = 4;
static mutex exclusive;

void Stack::push(int val, int debug_thread_info) 
{
    while (true) {
        Node * new_obj = new Node(val);
        if (new_obj == NULL) {return;}
        new_obj->extra_info = debug_thread_info;

        Node *next_ptr = this->_top;
        new_obj->next = next_ptr;
        
        // 将栈顶指针指向新节点，CAS 直到成功
        if (this->_top.compare_exchange_weak(next_ptr, new_obj)) {
            return;
        }
    }
}

Node* Stack::pop() 
{
    while (true) {
        Node *cur_ptr = this->_top;
        if (!cur_ptr) {
            return NULL;
        }
        Node *next_ptr = cur_ptr->next;
        // 将栈顶指针指向下一节点，CAS 直到成功
        if (this->_top.compare_exchange_weak(cur_ptr, next_ptr)) {
            return cur_ptr;
        }
    }
}

void Stack::print()
{
    exclusive.lock();
    int count = 0;
    Node * p = this->_top;
    while(p != NULL)
    {
        printf("[%d, %d] -> ", p->val, p->extra_info);
        p = p->next;
        count++;
    }
    printf("\nstack count : %d\n", count);
    exclusive.unlock();
}

Stack stack;

int stack_push(int val,int thread_info)
{
    stack.push(val, thread_info);
    printf("thread id : %lu, push_val %d , info %d\n"
        , std::this_thread::get_id(), val, thread_info);
    return 0;
}

int stack_pop()
{
    Node * node = stack.pop();
    if (node == NULL)
    {
        printf("thread id : %d, empty \n", std::this_thread::get_id());
        return 0;
    }
    printf("thread id : %d, pop %d \n"
            , std::this_thread::get_id(), node->val);
    stack.print();
    return 0;
}

bool randbool()
{
    //if (rand() % 2 == 0) {return false;}
    return true;
}

void task(int thread_id) 
{
    for (int i = 0; i < TASK_REPEATED_TIMES; i++)
    {
        if (randbool())
        {
            stack_push(i, thread_id);
        }
        else
        {
            stack_pop();
        }
    }
}

int main()
{
    thread thead_arr[THREAD_NUM];

    for (int i = 0; i < THREAD_NUM; i++)
    {
        int thread_info = i * 1000;
        thead_arr[i] = thread(task, thread_info);
    }

    for (int i = 0; i < THREAD_NUM; i++)
    {
        thead_arr[i].join();
    }

    stack.print();
    return 0;
}