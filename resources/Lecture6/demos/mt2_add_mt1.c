#include "threading.h"
#include <stdint.h>
#include <stdio.h>

static uint64_t mt_val = 0;
static uint64_t val = 0;


void single_thread_add() {
    for(uint32_t i = 0; i <= 10000000; ++i) {
        val += i;
    }
}

int thrd_proc_zero(void *arg) {
    uint64_t local = 0;
    for(uint32_t i = 0; i < 5000000; ++i) {
        local += i;
    }
    // accessing the shared variable only once reduces the possibility 
    // of multiple threads trying to access it at the same time
    mt_val += local;

    return 0;
}

int thrd_proc_one(void *arg) {
    uint64_t local = 0;
    for(int i = 5000000; i <= 10000000; ++i) {
        local += i;
    }
    mt_val += local;

    return 0;
} 

int main() {

    thrd_t threads[2], my_thread;
    thrd_create(&threads[0], thrd_proc_zero, 0);
    thrd_create(&threads[1], thrd_proc_one, 0);
    
    thrd_join(threads[0], 0);
    thrd_join(threads[1], 0);
    printf("Multithreaded add:   %llu\n", (unsigned long long)mt_val);

    single_thread_add();
    printf("Single threaded add: %llu\n", (unsigned long long)val);
}
