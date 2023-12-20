#include "threading.h"
#include <stdlib.h>
#include <stdio.h>

#define BUFFER_SIZE 256

struct mem {
    int32_t is_ready;
    char *buffer;
};

struct mem my_memory = { 0 };

int thrd_proc_init_memory(void *arg) {
    my_memory.buffer = (char*)malloc(BUFFER_SIZE);
    // Creates a software barrier that tells the compiler
    // not to reorder the code
    SOFTWARE_BARRIER;
    HARDWARE_BARRIER;

    // tells the CPU to not reorder instructions 
    my_memory.is_ready = 1;
    return 0;
}

int thrd_proc_read_data(void *arg){
    while(!my_memory.is_ready) {}
    printf("Enter something: \n");
    (void)!fgets(my_memory.buffer, BUFFER_SIZE, stdin);
    return 0;
}

int main() {
    thrd_t threads[2];
    thrd_create(&threads[0], thrd_proc_init_memory, 0);
    thrd_create(&threads[1], thrd_proc_read_data, 0);

    thrd_join(threads[0], 0);
    thrd_join(threads[1], 0);

    printf("%s\n", my_memory.buffer);
}