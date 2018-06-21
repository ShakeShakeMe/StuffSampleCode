/*
    This is a part of Tocy's Sample Code
    demo to implement compile interpostion
    https://git.oschina.net/Tocy/SampleCode.git
    
    compile:
    gcc -c main.cpp
    gcc -Wl,--wrap,malloc -Wl,--wrap,free -o intpos main.o mymalloc.o
*/

#include <stdio.h>
#include <stdlib.h>

int main()
{
    void * p = malloc(200);
    free(p);
    return 0;
}
