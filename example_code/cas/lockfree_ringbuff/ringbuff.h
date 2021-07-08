#ifndef __RINGBUFF_H__
#define __RINGBUFF_H__

#include <string.h>
#include <atomic>

const unsigned int MAX_BUFF_SIZE = 1024 * 1000;

template <typename T>
class RingBuff
{
    public:
        RingBuff()
        {
            memset(&ring_buff[0], 0, sizeof(ring_buff[0]) * MAX_BUFF_SIZE);
            this->head_idx = 0;
            this->tail_idx = 0;
            // printf("ringbuff init, size %d, use lock %d \n"
            //        , MAX_BUFF_SIZE, use_lock());
        }

        int enqueue_unlock(const T &ele)
        {
            if (is_full()) {return -1;}
        
            head_idx = (head_idx+1)%MAX_BUFF_SIZE;
            ring_buff[head_idx] = ele;
            return 0;
        }

        int enqueue_lock(const T &ele)
        {
            while (true)
            {
                if (is_full()) {return -1;}

                unsigned int cur_head  = this->head_idx; 
                unsigned int next_head = (head_idx+1)%MAX_BUFF_SIZE;
                ring_buff[next_head] = ele;
                if (this->head_idx.compare_exchange_weak(cur_head, next_head))
                {
                    return 0;
                }
            }
            return 0;
        }

        int enqueue(const T &ele)
        {
            if (use_lock())
            {
                return enqueue_lock(ele);
            }
            else 
            {
                return enqueue_unlock(ele);
            } 
        }

        int dequeue_unlock(T &ele)
        {
            if (is_empty()) {return -1;}
            tail_idx = (tail_idx + 1) % MAX_BUFF_SIZE;
            ele = ring_buff[tail_idx];
            return 0;
        }

        int dequeue_lock(T &ele)
        {
            while (true)
            {
                unsigned int cur_tail = this->tail_idx;
                unsigned int next_tail = (this->tail_idx + 1) % MAX_BUFF_SIZE;
                if (this->tail_idx.compare_exchange_weak(cur_tail, next_tail))
                {
                    return 0;
                }
            }
            return 0;
        }

        int dequeue(T &ele)
        {
            if (use_lock())
            {
                return dequeue_lock(ele);
            }
            else
            {
                return dequeue_unlock(ele);
            }
        }

        bool is_empty()
        {
            if (head_idx == tail_idx) {return true;}
            return false;
        }

        bool is_full()
        {
            if ((head_idx + 1) % MAX_BUFF_SIZE == tail_idx) {return true;}
            return false;
        }
        
        int get_size()
        {
            if (is_empty()) {return 0;}

            if (is_full()) {return MAX_BUFF_SIZE-1;}

            if (head_idx - tail_idx > 0)
            {
                return head_idx - tail_idx;
            }
            else 
            {
                return head_idx + (MAX_BUFF_SIZE - tail_idx);
            }
        } 

        bool use_lock()
        {
            #ifdef USE_LOCK
                return true;
            #else
                return false;
            #endif
        }

    private:
        T ring_buff[MAX_BUFF_SIZE];
        std::atomic<unsigned int> head_idx;
        std::atomic<unsigned int> tail_idx;
};

#endif 