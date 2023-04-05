#include <cstdio>
#include <cstring>
#include <thread>
#include <iostream>
#include <memory>
#include <assert.h>
#include <mutex>
#include "memery_op.h"

using namespace std;

int total_mem_alloc = 0;

new_ptr_list_t ptr_list_head;
std::mutex new_output_lock;
std::mutex new_ptr_lock;

void print_position(const char * file, unsigned line)
{
    printf("check file %s, line %d", file, line);
    return;
}

void print_position(void * addr, unsigned line)
{
    printf("check file %p, line %d", addr, line);
    return;
}

static void* alloc_mem(std::size_t size, const char* file
        , int line, bool is_array) 
{
    assert(line >= 0);
    
    printf("alloc size %d, from file <%s,%d> \n", size, file, line);
    std::size_t s = size + ALIGNED_LIST_ITEM_SIZE;
    new_ptr_list_t* ptr = (new_ptr_list_t*)malloc(s);
    if (ptr == nullptr) 
    {
        std::unique_lock<std::mutex> lock(new_output_lock);
        printf("Out of memory when allocating %lu bytes\n"
                , (unsigned long)size);
        abort();
    }
    void* usr_ptr = (char*)ptr + ALIGNED_LIST_ITEM_SIZE;
    if (line) 
    {
        strncpy(ptr->file, file
            , _DEBUG_NEW_FILENAME_LEN - 1)[_DEBUG_NEW_FILENAME_LEN - 1] = '\0';
    } 
    else 
    {
        ptr->addr = (void*)file;
    }

    ptr->line = line;
    ptr->is_array = is_array;
    ptr->size = size;
    ptr->magic = DEBUG_NEW_MAGIC;
    {
        ptr->next = ptr_list_head.next;
        if (ptr_list_head.next != NULL)
        {
            ptr_list_head.next->prev = ptr;
        }
        
        ptr->prev = &ptr_list_head;
        ptr_list_head.next = ptr;
    }
    total_mem_alloc += size;
    return usr_ptr;
}

static void free_pointer(void* usr_ptr, void* addr, bool is_array) 
{
    if (usr_ptr == nullptr) {return;}

    new_ptr_list_t* ptr = (new_ptr_list_t*)((char*)usr_ptr - ALIGNED_LIST_ITEM_SIZE);
    {
        std::unique_lock<std::mutex> lock(new_ptr_lock);
        total_mem_alloc -= ptr->size;
        ptr->magic = 0;
        printf("free pointer, object at %p (size %lu, ", usr_ptr, (unsigned long)ptr->size);
        if (ptr->line != 0) 
        {
            print_position(ptr->file, ptr->line);
        } else 
        {
            print_position(ptr->addr, ptr->line);
        }
        printf(")\n");

        ptr->prev->next = ptr->next;
        if (ptr->next != NULL)
        {
            ptr->next->prev = ptr->prev;
        }
    }
    free(ptr);
}

void * operator new(size_t size)
{
    return alloc_mem(size, __FILE__, __LINE__, false); 
}

void * operator new(size_t size, const char *file, unsigned int line) 
{
    if (void *ptr = alloc_mem(size, file, line, false)) 
    {
        return ptr;
    }
    throw std::bad_alloc();
}

void operator delete(void* ptr)  
{
    free_pointer(ptr, nullptr, false); 
}

int checkLeaks() 
{
    int leak_cnt = 0;
    int whitelisted_leak_cnt = 0;
    new_ptr_list_t* ptr = ptr_list_head.next;

    while (ptr != NULL) 
    {
        const char* const usr_ptr = (char*)ptr + ALIGNED_LIST_ITEM_SIZE;
        printf("Leaked object at %p (size %lu, ", usr_ptr, (unsigned long)ptr->size);
        if (ptr->line != 0) 
        {
            print_position(ptr->file, ptr->line);
        } else 
        {
            print_position(ptr->addr, ptr->line);
        }
        printf(")\n");
        ptr = ptr->next;
        ++leak_cnt;
    }
    return leak_cnt;
}
