#include <stdio.h>
#include <stdlib.h>
#include <setjmp.h>

jmp_buf env;

int my_func(int a, int b) 
{
    if (b == 0) {
        printf("do not allow division by 0\n");
        longjmp(env, 1);
    }
    return a / b;
}

int main(int argc, char const *argv[]) 
{
    int res = setjmp(env);
    if (res == 0) {
        printf("return from setjmp\n");
        my_func(10, 0);
    } else {
        printf("return from longjmp: %d\n", res);
    }
    return 0;
}
