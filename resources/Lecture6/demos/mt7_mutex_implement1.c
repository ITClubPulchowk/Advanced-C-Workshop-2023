#include "threading.h"
#include <stdint.h>
#include <stdio.h>

typedef struct Mutex {
    volatile uint32_t value;
} Mutex;

static uint64_t result = 0;

static uint64_t mt_result = 0;
static Mutex mutex_result;

static void MutexInit(Mutex *mutex) {
    mutex->value = 0;
}

static void MutexLock(Mutex *mutex) {
    while(mutex->value) {}
    mutex->value = 1;
}

static void MutexUnlock(Mutex *mutex) {
    mutex->value = 0;
}

int thrd_proc_zero(void *arg) {
    for(int i = 0; i < 50000; ++i) {
        MutexLock(&mutex_result);
        mt_result += i;
        MutexUnlock(&mutex_result);
    }
    return 0;
}

int thrd_proc_one(void *arg) {
    for(int i = 50000; i <= 100000; ++i) {
        MutexLock(&mutex_result);
        mt_result += i;
        MutexUnlock(&mutex_result);
    }
    return 0;
}

void single_threaded_add() {
    for(int i = 0; i <= 100000; ++i){
        result += i;
    }
}

int main() {
    MutexInit(&mutex_result);

    thrd_t threads[2];
    thrd_create(&threads[0], thrd_proc_zero, 0);
    thrd_create(&threads[1], thrd_proc_one, 0);

    thrd_join(threads[0], 0);
    thrd_join(threads[1], 0);

    printf("Multithreaded:   %llu\n", (unsigned long long)mt_result);
    
    single_threaded_add();
    printf("Single threaded: %llu\n", (unsigned long long)result);

}