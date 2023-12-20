#include "threading.h"
#include <stdint.h>
#include <stdio.h>

static uint64_t mt_val = 0;
static uint64_t val = 0;

int thrd_proc_zero(void *arg) {
    for(uint32_t i = 0; i < 500000; ++i) {
        interlocked_add64(&mt_val, i);
    }
    return 0;
}

int thrd_proc_one(void *arg) {
    for(uint32_t i = 500000; i <= 1000000; ++i) {
        interlocked_add64(&mt_val, i);
    }
    return 0;
} 

void single_thread_add() {
    for(uint32_t i = 0; i <= 1000000; ++i) {
        val += i;
    }
}

int main() {

    thrd_t threads[2];
    thrd_create(&threads[0], thrd_proc_zero, 0);
    thrd_create(&threads[1], thrd_proc_one, 0);
    
    thrd_join(threads[0], 0);
    thrd_join(threads[1], 0);
    printf("Multithreaded add:   %llu\n", (unsigned long long)mt_val);

    single_thread_add();
    printf("Single threaded add: %llu\n", (unsigned long long)val);

}
