#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>
/*
此种方法只能锁整个文件，访问被锁的文件后回直接返回
*/
int main(int argc, char *argv[])
{
    int fdB;
    FILE *pA;

    fdB = open("B.lock", O_CREAT | O_EXCL, 0644);
    if (fdB < 0 && errno == EEXIST)
    {
        // 其实是判断文件B.lock是否已经存在
        printf("File A.dat is already locked.\n");
        return -1;
    }
    else if (fdB < 0)
    {
        perror("error");
        return -1;
    }

    //下面进行对文件A.dat的访问
    pA = fopen("./A.dat", "w");
    //...
    if(pA != NULL)
    {
        fprintf(pA, "This is testing for fprintf...\n");
        printf("write file \n");
        fclose(pA);
    }
    else
    {
        printf("if(pA == NULL) \n");
    }

    sleep(5);
    close(fdB);
    unlink("B.lock"); // 去掉对加锁文件的引用，删除 "B.lock"
    return 0;
}
