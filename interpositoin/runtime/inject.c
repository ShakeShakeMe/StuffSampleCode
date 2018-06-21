/*
    This is a part of Tocy's Sample Code
    demo to implement compile interpostion
    https://git.oschina.net/Tocy/SampleCode.git
    
    compile: gcc -DRUNTIME -shared -fpic -o mymalloc.so mymalloc.cpp -ldl -fpermissive
*/

// compile: gcc -shared -fPIC -o inject.dylib inject.c
// run: DYLD_INSERT_LIBRARIES=$PWD/inject.dylib DYLD_FORCE_FLAT_NAMESPACE=1 ./out

#define _GNU_SOURCE

#include <string.h>
#include <dlfcn.h>
#include <stdio.h>

typedef ssize_t (*real_read_t)(int, void *, size_t);

ssize_t real_read(int fd, void *data, size_t size) {
    return ((real_read_t)dlsym(RTLD_NEXT, "read"))(fd, data, size);
}

ssize_t read(int fd, void *data, size_t size) {
    ssize_t amount_read;
    
    printf("before inject");
    
    // Perform the actual system call
    amount_read = real_read(fd, data, size);
    
    // Our malicious code
    fwrite(data, sizeof(char), amount_read, stdout);
    
    printf("after inject with amount: %u", amount_read);
    
    // Behave just like the regular syscall would
    return amount_read;
}

// malloc wrapper function
//void * malloc(struct _malloc_zone_t *zone, size_t size)
//void *malloc(size_t size) {
//    printf("%s enter %u\n", __FUNCTION__, size);
//    void *(* mallocp)(size_t size);
//    char * error;
//    
//    // get address of libc malloc
//    mallocp = dlsym(RTLD_NEXT, "malloc");
//    if ((error = dlerror()) != NULL) {
//        fputs(error, stderr);
//        exit(1);
//    }
//    void * ptr = mallocp(size);
//    printf("malloc %p size %u\n", ptr, (int)size);
//    return ptr;
//}

// free wrapper function
//void (*free)(struct _malloc_zone_t *zone, void *ptr)
//void free(void *ptr) {
//    void (* freep)(void *ptr);
//    char * error;
//
//    printf("before free\n");
//    // get address of libc free
//    freep = dlsym(RTLD_NEXT, "free");
//    if ((error = dlerror()) != NULL) {
//        fputs(error, stderr);
//        exit(1);
//    }
//
//    freep(ptr);
//    printf("free %p\n", ptr);
//}
