
// condition条件变量
// 线程使用condition同步
// 使用基本的condition api 写一个例子

#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

pthread_mutex_t count_lock;
pthread_cond_t count_nonzero;
unsigned count = 0;

void * decrement_count(void * arg)
{
    pthread_mutex_lock(&count_lock);
    printf("[< decrement_count] get count_lock \n");
    while(count == 0)
    {
        printf("[< decrement_count] count == 0 \n");
        printf("[< decrement_count] before cond_wait \n");
        pthread_cond_wait(&count_nonzero, &count_lock);
        printf("[< decrement_count] after cond_wait \n");
    }

    count = count + 1;
    pthread_mutex_unlock(&count_lock);
}

void * increment_count(void *arg)
{
    pthread_mutex_lock(&count_lock);
    printf("[>increment_count] get count_lock \n");
    if(count == 0)
    {
        printf("[>increment_count] before cond_signal \n");
        pthread_cond_signal(&count_nonzero);
        printf("[>increment_count] after cond_signal \n");
    }
    count = count + 1;
    pthread_mutex_unlock(&count_lock);
}

int main(void)
{
    printf("in main\n");
    pthread_t tid1, tid2;

    pthread_mutex_init(&count_lock, NULL);
    pthread_cond_init(&count_nonzero, NULL);

    pthread_create(&tid1, NULL, decrement_count, NULL);
    sleep(1);
    pthread_create(&tid2, NULL, increment_count, NULL);

    sleep(5);
    pthread_exit(0);

    return 0;
}

// g++ -g condition.cc -lpthread

// in main
// [< decrement_count] get count_lock
// [< decrement_count] count == 0
// [< decrement_count] before cond_wait
// [>increment_count] get count_lock
// [>increment_count] before cond_signal
// [>increment_count] after cond_signal
// [< decrement_count] after cond_wait