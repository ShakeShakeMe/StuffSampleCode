/*
    This is a part of Tocy's Sample Code
    demo to implement compile interpostion
    https://git.oschina.net/Tocy/SampleCode.git
    
    compile: gcc -DLINK_TIME -c mymalloc.cpp
*/

#ifdef LINK_TIME
#include <stdio.h>

extern "C"
{
    void * __real_malloc(size_t size);
    void __real_free(void * ptr);

    // malloc wrapper function
    void * __wrap_malloc(size_t size)
    {
        printf("%s enter %u\n", __FUNCTION__, size);
        void * ptr = __real_malloc(size);
        printf("malloc %p size %u\n", ptr, size);
        return ptr;
    }

    // free wrapper function
    void __wrap_free(void *ptr)
    {
        __real_free(ptr);
        printf("free %p\n", ptr);
    }
}
#endif
