#include <iostream>
#include <stdio.h>
#include <assert.h>
#include <thread>
#include "../ringbuff.h"

using namespace std; 
const int THREAD_NUM = 4;
const int TASK_REPEATED_TIMES = 10;

RingBuff<int> thread_ring_buff;

void single_test()
{
    int enqueue = 10;
    RingBuff<int> ring_buff;
    ring_buff.enqueue(enqueue);
    
    int dequeue = 0;
    ring_buff.dequeue(dequeue);
    assert(enqueue == dequeue);
    return;
}

void size_test()
{
    int push_num = 100;
    RingBuff<int> ring_buff;
    for (int i = 0; i < push_num; i++)
    {
        ring_buff.enqueue(i);
    }
    assert(ring_buff.get_size() == push_num);
    return;
}

void empty_test()
{
    RingBuff<int> ring_buff;
    assert(ring_buff.is_empty());
    return;
}

void full_test()
{
    RingBuff<int> ring_buff;
    for (unsigned int i = 0; i < MAX_BUFF_SIZE - 1; i++)
    {
        ring_buff.enqueue((int)i);
    }
    assert(ring_buff.is_full());
    return;
}

void push_test()
{
    RingBuff<int> ring_buff;
    unsigned int half = MAX_BUFF_SIZE / 2;
    for (unsigned int i = 0; i < half; i++)
    {
        ring_buff.enqueue((int)i);
    }

    for (unsigned int i = 0; i < half; i++)
    {
        int dequeue = 0;
        ring_buff.dequeue(dequeue);
        assert(dequeue == i);
    }

    for (unsigned int i = 0; i < MAX_BUFF_SIZE - 1; i++)
    {
        ring_buff.enqueue((int)i);
    }

    for (unsigned int i = 0; i < MAX_BUFF_SIZE - 1; i++)
    {
        int dequeue = 0;
        ring_buff.dequeue(dequeue);
        assert(dequeue == i);
    }
    assert(ring_buff.is_empty());
    return;
}

int multi_datatype_test()
{
    {
        char enqueue = 'a';
        RingBuff<char> ring_buff;
        ring_buff.enqueue(enqueue);
        
        char dequeue = '0';
        ring_buff.dequeue(dequeue);
        assert(enqueue == dequeue);
    }

    {
        unsigned long long enqueue = 100;
        RingBuff<unsigned long long> ring_buff;
        ring_buff.enqueue(enqueue);
        
        unsigned long long dequeue = 0;
        ring_buff.dequeue(dequeue);
        assert(enqueue == dequeue);
    }
    return 0;
}

void thread_enqueue(int thread_info)
{
    for (int i = 0; i < TASK_REPEATED_TIMES; i++)
    {
        thread_ring_buff.enqueue(thread_info * 10000 + i);
    }
    return;
}

void thread_dequeue()
{
    for (int i = 0; i < TASK_REPEATED_TIMES; i++)
    {
        int value = 0;
        thread_ring_buff.dequeue(value);
    }
    return;
}

int multi_thread_test()
{
    // enqueue
    thread thead_arr[THREAD_NUM];
    for (int i = 0; i < THREAD_NUM; i++)
    {
        thead_arr[i] = thread(thread_enqueue, i);
    }

    for (int i = 0; i < THREAD_NUM; i++)
    {
        thead_arr[i].join();
    }
    assert(thread_ring_buff.get_size() == THREAD_NUM * TASK_REPEATED_TIMES);

    // dequeue
    thread thead_arr_deque[THREAD_NUM];
    for (int i = 0; i < THREAD_NUM; i++)
    {
        thead_arr_deque[i] = thread(thread_dequeue);
    }
    for (int i = 0; i < THREAD_NUM; i++)
    {
        thead_arr_deque[i].join();
    }
    assert(thread_ring_buff.get_size() == 0);
    return 0;
}

int main()
{
    single_test();
    size_test();
    empty_test();
    full_test();
    push_test();
    multi_datatype_test();
    multi_thread_test();
    return 0;
}