#include <stdio.h>

void ping();
void pong();

void ping()
{
    printf("ping\n");
    pong();
}

void pong()
{
    printf("pong\n");
    ping();
}

int main(int argc, char *argv[])
{
    ping();
    return 0;
}

// 运行结果：
// [1]    431 segmentation fault (core dumped)  ./a.out