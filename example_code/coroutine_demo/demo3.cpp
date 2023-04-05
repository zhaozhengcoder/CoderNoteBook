#include <stdio.h>
#include <ucontext.h>
#include <unistd.h>

const int MAX_COUNT = 5;

static ucontext_t uc[4];
static int count = 0;
static int first_entry = 0;

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
    getcontext(&uc[3]);

    printf("begin , is_first_entry %d \n", first_entry);

    if (first_entry == 0)
    {
        first_entry++;

        uc[1].uc_link = &uc[3];     //
        uc[1].uc_stack.ss_sp = st1; //
        uc[1].uc_stack.ss_size = sizeof st1;
        makecontext(&uc[1], ping, 0);

        uc[2].uc_link = &uc[3];     //
        uc[2].uc_stack.ss_sp = st2; //
        uc[2].uc_stack.ss_size = sizeof st2;
        makecontext(&uc[2], pong, 0);

        // start ping-pong
        swapcontext(&uc[0], &uc[1]);
    }
    printf("end \n");

    return 0;
}