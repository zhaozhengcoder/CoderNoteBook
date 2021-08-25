#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
 
void function()
{
    while(1)
    {
	    printf("hello,function!\n");
        sleep(1);
    }
}
 
void test()
{
    int val = 10;
    printf("val %d\n", val);
    
    // set val = 11
    asm("movl $0xb, -0x4(%rbp)");
    printf("val %d\n", val);
    
    long addr = function;
    asm("movl $0x401156, 0x18(%rbp)");
}
 
int main()
{
    printf("addr %p \n", &function);
	test();
	printf("hello,world!\n");
	return 0;
}

// https://blog.csdn.net/yiftss/article/details/89474622