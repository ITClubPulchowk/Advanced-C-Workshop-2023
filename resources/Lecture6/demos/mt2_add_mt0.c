#include "threading.h"
#include <stdio.h>

// multihreaded result
static uint64_t mt_val = 0;

//single threaded result
static uint64_t val = 0;

int thrd_proc_zero(void *arg) {
    for(uint32_t i = 0; i < 50000; ++i) {
        mt_val += i;
    }
    return 0;
}

int thrd_proc_one(void *arg) {
    for(uint32_t i = 50000; i <= 100000; ++i) {
        mt_val += i;
    }
    return 0;
} 

void single_thread_add() {
    for(uint32_t i = 0; i <= 100000; ++i) {
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


    // Perform same operation inside a single thread for comparision
    single_thread_add();
    printf("Single threaded add: %llu\n", (unsigned long long)val);

}
