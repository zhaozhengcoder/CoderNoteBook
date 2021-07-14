#include <stdio.h>
#include <string.h>

int main(void) {
    printf("Calling the fopen() function...\n");

    FILE *fd = fopen("test.txt", "r");
    if (!fd) {
        printf("fopen() returned NULL\n");
    }

    printf("fopen() succeeded\n");

    char passwd1[] = "password123";
    char passwd2[] = "password3435";
    if (!strcmp(passwd1, passwd2))
    {
        printf("Correct Password!\n");
        return 0;
    }  
    printf("unCorrect Password!\n");
    return 0;
}

// gcc -Wall -fPIC -shared -o myfopen.so myfopen.c -ldl
// gcc prog.c -o prog
// LD_PRELOAD=./myfopen.so ./prog
// unset LD_PRELOAD