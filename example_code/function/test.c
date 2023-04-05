#include <stdio.h>
#include <string.h>
#include <signal.h>
#include <dlfcn.h>
#include <errno.h>
#include <stdint.h>
#include <sys/mman.h>
#include <unistd.h>

int MyFunction(int x, int y);
int MyFunctionNew(int x, int y);

char new_func[] = 
{
   0x55,
   0x48, 0x89, 0xe5, 
   0x89, 0x7d, 0xec, 
   0x89, 0x75, 0xe8, 

   0xc7, 0x45, 0xfc, 0x0a, 0x00, 0x00, 0x00,

   0xc7, 0x45, 0xf8, 0x01, 0x00, 0x00, 0x00, 

   0x8b, 0x45, 0xfc, 
   0x5d, 
   0xc3  
};

void sig_user1_handler(int sig, siginfo_t *si, void *data)
{
    int pagesize = sysconf(_SC_PAGE_SIZE);
    if (pagesize < 0) {
        pagesize = 4096;
    }

    int len = sizeof(new_func);

    uintptr_t addr = (((uintptr_t)MyFunction) / pagesize) * pagesize;
    fprintf(stderr, "%s: iminus: %p, aligned: 0x%lx, sz %d\n", __func__, MyFunction, addr, len);
    if (mprotect((void*)addr, (uintptr_t)MyFunction - addr + len, PROT_WRITE|PROT_READ|PROT_EXEC) < 0) {
        fprintf(stderr, "%s\n", strerror(errno));
    }

    memcpy((void*)MyFunction, (void*)new_func, len);

    if (mprotect((void*)addr, (uintptr_t)MyFunction - addr + len, PROT_READ|PROT_EXEC) < 0) {
        fprintf(stderr, "%s\n", strerror(errno));
    }
}

int MyFunction(int x, int y)
{
    int a, b;
    a = 10;
    b = 1;

    int val = a * x + b * y;
    return val;
}

int MyFunctionNew(int x, int y)
{
    int a = 10;
    return a;
}

int main()
{ 
    struct sigaction newact, oldact;
    sigemptyset(&newact.sa_mask);
    newact.sa_sigaction = sig_user1_handler;
    sigaction(SIGUSR1, &newact, &oldact);

    void * ptr = &MyFunction;
    printf("addr %p , sizeof %d\n", ptr, sizeof(new_func));

    int a = 10;
    int b = 10;

    while (1)
    {
        int val = MyFunction(a, b);
        printf("val : %d \n", val);
        sleep(3);
    }
    return 0;
}
