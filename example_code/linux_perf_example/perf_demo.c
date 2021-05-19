#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>
#include <signal.h>
#include <sys/param.h>
#include <sys/stat.h>

int func1()
{
    int val = 0;
    for(int i=0;i<100000000;i++)
    {
        val = val * i;
    }
    return val;
}

int func2()
{
    int val = 0;
    for (int i=0;i<50;i++)
    {
        val = val * func1();
        usleep(100);
        printf("test print %d \n",i);
    }
    return val;
}

int main()
{
    func2();
}