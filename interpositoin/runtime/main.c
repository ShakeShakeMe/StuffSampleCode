/*
    This is a part of Tocy's Sample Code
    demo to implement compile interpostion
    https://git.oschina.net/Tocy/SampleCode.git
    
    compile: gcc -o intpos main.cpp
    run: LD_PRELOAD="./mymalloc.so" ./intpos
*/

//#include <stdio.h>
//#include <stdlib.h>
//
//int main()
//{
//    void * p = malloc(200);
//    free(p);
//    return 0;
//}


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, const char *argv[]) {
    char buffer[1000];
    int amount_read;
    int fd;
    
    fd = fileno(stdin);
    if ((amount_read = read(fd, buffer, sizeof buffer)) == -1) {
        perror("error reading");
        return EXIT_FAILURE;
    }
    
    if (fwrite(buffer, sizeof(char), amount_read, stdout) == -1) {
        perror("error writing");
        return EXIT_FAILURE;
    }
    
    return EXIT_SUCCESS;
}
