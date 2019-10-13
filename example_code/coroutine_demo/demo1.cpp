#include <stdio.h>
#include <ucontext.h>
#include <unistd.h>

const int MAX_COUNT = 5;

static ucontext_t uc[3];
static int count = 0;

void ping();
void pong();

void ping()
{
    while (count < MAX_COUNT)
    {
        printf("ping %d\n", ++count);
        // yield to pong
        sleep(1);
        swapcontext(&uc[1], &uc[2]); // 保存当前context于uc[1],切换至uc[2]的context运行
        printf("ping -> end \n");
    }
}

void pong()
{
    while (count < MAX_COUNT)
    {
        printf("pong %d\n", ++count);
        // yield to ping
        sleep(1);
        swapcontext(&uc[2], &uc[1]); // 保存当前context于uc[2],切换至uc[1]的context运行
        printf("pong -> end \n");
    }
}

char st1[8192];
char st2[8192];

int main(int argc, char *argv[])
{

    // initialize context
    printf("times %d \n", MAX_COUNT);
    getcontext(&uc[1]);
    getcontext(&uc[2]);

    printf("begin \n");

    uc[1].uc_link = &uc[0];     // 这个玩意表示uc[1]运行完成后，会跳至uc[0]指向的context继续运行
    uc[1].uc_stack.ss_sp = st1; // 设置新的堆栈
    uc[1].uc_stack.ss_size = sizeof st1;
    makecontext(&uc[1], ping, 0);

    uc[2].uc_link = &uc[0];     // 这个玩意表示uc[2]运行完成后，会跳至uc[0]指向的context继续运行
    uc[2].uc_stack.ss_sp = st2; // 设置新的堆栈
    uc[2].uc_stack.ss_size = sizeof st2;
    makecontext(&uc[2], pong, 0);

    // start ping-pong
    swapcontext(&uc[0], &uc[1]);

    // 将当前context信息保存至uc[0],跳转至uc[1]保存的context去执行
    // 这里我稍微要多说几句，因为我迷惑过，我曾经困惑的一点在于uc[0]，为什么uc[0]不需要设置堆栈的信息？
    // 因为swapcontext已经帮我们做好了一切，swapcontext函数会将当前点的信息保存在uc[0]中
    // 当然我们没有设置的话，默认的堆栈一定是主堆栈啦
    printf("end \n");

    return 0;
}