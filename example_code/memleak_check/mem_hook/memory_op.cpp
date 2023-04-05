#include <iostream>
#include <memory>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

extern "C" void * __real_malloc(size_t size);
extern "C" void __real_free(void *ptr);

void * operator new (size_t size) 
{ 
    cout << endl << "new size : " << size << endl ;
    void *p = malloc(size); 
    return p;
} 

void * operator new[] (size_t size) 
{ 
    cout << endl << "new size[] : " << size << endl ;
    void *p = malloc(size); 
    return p;
} 

void* operator new (size_t size , const char *file , 
        unsigned int line ) {
    if (void *ptr = malloc (size)) 
    {
        cout << endl << "new size : " << size <<", file : " << file << " "<< line << endl ;
        return ptr ;
    }  
    throw std::bad_alloc () ;
}

void operator delete (void *ptr ) 
{
    if (ptr == nullptr) return ;

    cout << ptr << "\tsource has been released !" << endl ;
    free (ptr);
    ptr = nullptr;
}


extern "C" void * __wrap_malloc(size_t size) {
    printf("my malloc: %zu\n", size);
    return __real_malloc(size);
}

extern "C" void __wrap_free(void *ptr) {
    printf("my free: %p\n", ptr);
    __real_free(ptr);
}