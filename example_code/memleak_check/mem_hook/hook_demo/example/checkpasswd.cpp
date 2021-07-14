
#include <stdio.h>
#include <string.h>
  
int main(int argc, char **argv)
{
    char passwd[] = "password";
    if (argc < 2)
    {
        printf("Usage: %s <password>\n", argv[0]);
        return 1;
    }   
  
    if (!strcmp(passwd, argv[1]))
    {
        printf("Correct Password!\n");
        return 0;
    }   
  
    printf("Invalid Password!\n");
    return 1;
}

// g++ -Wall -fPIC -shared -o hack.so hack.cpp -ldl
// g++ checkpasswd.cpp -o checkpasswd
// LD_PRELOAD=./hack.so ./checkpasswd 90