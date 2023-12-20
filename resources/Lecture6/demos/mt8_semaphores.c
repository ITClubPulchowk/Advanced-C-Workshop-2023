#include "threading.h"
#include <stdio.h>
#include <stdlib.h>

#define THRD_COUNT 5

struct {
    char *buffer;
} my_memory;
sem_t sem;

int thrd_proc_write_data(void *arg) {
    int index = (int)(int64_t)arg;


        while(1) {
            /*
                sem_wait(
                    sem_t *sem     => Pointer to a semaphore to wait for
                )
            */
            sem_wait(&sem);
            printf("Thread %d: ", index);
            printf("%s", my_memory.buffer);
        }

    return 0;
}

int main() {
    
    // Create 5 threads that do identical work
    thrd_t my_threads[THRD_COUNT];
    for(int i = 0; i < THRD_COUNT; ++i) {
        thrd_create(&my_threads[i], thrd_proc_write_data, (void*)(int64_t)i);
    }

    /*
        sem_init(
            sem_t *sem      => A location to store the created semaphore
            int pshared     => Sharing access for semaphore
            int value       => Initial value for the semaphore
        )
    */
    sem_init(&sem, 0, 0);

    my_memory.buffer = (char*)malloc(256);

    int lines_to_read = 10;
    printf("Enter something:\n");
    for(int i = 0; i < lines_to_read; ++i) {

        // Read one line from console
        (void)!fgets(my_memory.buffer, 256, stdin);
        if(*my_memory.buffer == '\n') break;

        /*
            sem_post (
                sem_t *sem    => The pointer to the semaphore to signal
            )
        */
        sem_post(&sem);
    }
}
