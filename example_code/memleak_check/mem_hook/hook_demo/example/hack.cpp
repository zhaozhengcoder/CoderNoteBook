#define _GNU_SOURCE

#include <stdio.h>
#include <dlfcn.h>

extern "C" int strcmp(const char *s1, const char *s2)
{
    printf("hack function invoked. s1=<%s> s2=<%s>\n", s1, s2);
    return 0;
}