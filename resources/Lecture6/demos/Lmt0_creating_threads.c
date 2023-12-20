#include <threads.h>
#include <stdio.h>


int thrd_proc(void *arg) {
    printf("Bond, James Bond\n");
    return 0;
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
    printf("To infinity and beyond\n");
}
