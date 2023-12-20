#include "threading.h"

#include <stdio.h>
#include <stdint.h>

static uint64_t value = 0;

int thrd_proc(void *arg) {
    for(uint32_t i = 0; i <= 100000; ++i) {
        value += i;
    }
    return 24;
}

int main() {
    // Unique thread identifier
    thrd_t my_thread;

    /*
        thrd_create (
            thrd_t *thr         => The thrd_t value to associate with the thread
            thrd_start_t func   => The starting point for execution of the thread
            void * arg          => The arguments to pass to the thread function
        )
    */
    thrd_create(&my_thread, thrd_proc, 0);

    int res;

    /*
        thrd_join (
            thrd_t thr          => The thread to wait for
            int *res            => The return value of the thread function
        )
    */
    thrd_join(my_thread, &res);
    printf("value: %llu return value: %d\n", (unsigned long long)value, res);
}
