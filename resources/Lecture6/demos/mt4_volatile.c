#include <stdio.h>
#include "threading.h"


int thrd_proc(void *arg) {
    thrd_sleep_millisecs(100);
    *(int*)arg = 1;
    return 0;
}

int main() {
    volatile int a;
    thrd_t my_thread;
    thrd_create(&my_thread, thrd_proc, (void*)&a);
    a = 0;

    while(!a) {
    }
    printf("hello there\n");
    thrd_join(my_thread, 0);
}
