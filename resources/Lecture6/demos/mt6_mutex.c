#include "threading.h"
#include <stdio.h>

FILE *file_handle;
mtx_t mutex_file;

int thrd_proc_transfer_data(void *arg) {
    char *file_name = (char*)arg;
    FILE *file_one;
    file_one = fopen(file_name, "r");

    /* 
        Technically mutex is not necessary here because fputs, even though not specified
        by the standard, is thread-safe(it uses a mutex itself) on most implementations.
        However, you may have a scenario where the read buffer is small, and you may need
        to perform read multiple times for a single line and have more than one 'fputs'.
        This is a common scenario in network programming where the data blocks are very 
        large to fit in a single buffer.
    */

    if(file_one) {
        char buffer[256];
        while(fgets(buffer, 256, file_one) != 0) {
            mtx_lock(&mutex_file);
            fputs(buffer, file_handle);
            mtx_unlock(&mutex_file);
        }

        fclose(file_one);
    }
    
    return 0;
}

int main() {
    file_handle = fopen("dest.txt", "w");
    mtx_init(&mutex_file, mtx_plain);

    if(file_handle) {
        thrd_t threads[2];
        thrd_create(&threads[0], thrd_proc_transfer_data, "src_one.txt");
        thrd_create(&threads[1], thrd_proc_transfer_data, "src_two.txt");

        thrd_join(threads[0], 0);
        thrd_join(threads[1], 0);

        fclose(file_handle);
    }
}