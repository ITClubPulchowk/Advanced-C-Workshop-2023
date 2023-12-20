#include "threading.h"
#include <stdint.h>
#include <stdio.h>

#define THRD_COUNT 10

int thrd_proc(void *arg) {
    int thrd_index = (int64_t)(arg);
    printf("Hello world from thread %d\n", thrd_index);
    return 0;
}

int main() {
    thrd_t threads[THRD_COUNT];

    for(int i = 0; i < THRD_COUNT; ++i) {
        thrd_create(&threads[i], thrd_proc, (void*)(int64_t)(i));
    }

    for(int i = 0; i < THRD_COUNT; ++i) {
        thrd_join(threads[i], 0);
    }
    
}
