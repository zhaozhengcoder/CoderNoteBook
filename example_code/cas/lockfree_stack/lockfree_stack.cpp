#include <atomic>
#include <cstddef>
#include <iostream>
#include <thread> 
#include "lockfree_stack.h"

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
    int count = 0;
    Node * p = this->_top;
    while (p != NULL)
    {
        printf("[%d, %d] -> ", p->val, p->extra_info);
        p = p->next;
        count++;
    }
    printf("\nstack count : %d\n", count);
}

int Stack::get_size()
{
    int size = 0;
    Node * p = this->_top;
    while (p != NULL)
    {
        p = p->next;
        size++;
    }
    return size;
}