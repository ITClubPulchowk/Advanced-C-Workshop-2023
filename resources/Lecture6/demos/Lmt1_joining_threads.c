#include <threads.h>
#include <stdio.h>


int thrd_proc(void *arg) {
    printf("Bond, James Bond\n");
    return 0;
}

int main() {
    // Unique thread identifier
    thrd_t my_thread;
    thrd_create(&my_thread, thrd_proc, 0);
    
    printf("To infinity and beyond\n");

    /*
        thrd_join (
            thrd_t thr          => The thread to wait for
            int *res            => The return value of the thread function
        )
    */
    thrd_join(my_thread, 0);
}
