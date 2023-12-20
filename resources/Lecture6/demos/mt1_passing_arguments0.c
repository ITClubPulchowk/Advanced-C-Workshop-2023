#include "threading.h"
#include <stdio.h>

int thrd_proc(void *arg) {

    // Cast back to char*
    char *msg = (char*)arg;
    printf("%s\n", msg);
    return 0;
}

int main() {
    thrd_t my_thread;
    thrd_create(&my_thread, thrd_proc, (void*)"May the force be with you\n");
    thrd_join(my_thread, 0);
}