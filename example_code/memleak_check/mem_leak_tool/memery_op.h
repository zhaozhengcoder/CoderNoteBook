#ifndef __MEMERY_OP_H__
#define __MEMERY_OP_H__

#include <iostream>

const int _DEBUG_NEW_FILENAME_LEN = 200;
const int DEBUG_NEW_MAGIC = 0xFFFF;
const int ALIGNED_LIST_ITEM_SIZE = 1024;

struct new_ptr_list_t 
{
    new_ptr_list_t* next;
    new_ptr_list_t* prev;
    std::size_t size;
    union 
    {
        char file[_DEBUG_NEW_FILENAME_LEN];
        void* addr;
    };
    unsigned line;
    bool is_array;
    int magic;

    new_ptr_list_t()
    {
        next = NULL;
        prev = NULL;
    }
};

int checkLeaks();
void * operator new(size_t size);
void * operator new(size_t size, const char *file, unsigned int line);
#endif 