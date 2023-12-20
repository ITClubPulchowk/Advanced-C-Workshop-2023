#include <stdio.h>
#include "threading.h"

mtx_t mutex1;
mtx_t mutex2;

int thread1_func(void *arg)
{
  printf("Thread 1 trying to lock mutex 1\n");
  mtx_lock(&mutex1);
  printf("Thread 1 locked mutex 1\n");
  
  thrd_sleep_millisecs(100);

  printf("Thread 1 trying to lock mutex 2\n");
  mtx_lock(&mutex2);
  printf("Thread 1 locked mutex 2\n");

  mtx_unlock(&mutex2);
  mtx_unlock(&mutex1);
  return 0;
}

int thread2_func(void *arg)
{
  printf("Thread 2 trying to lock mutex 2\n");
  mtx_lock(&mutex2);
  printf("Thread 2 locked mutex 2\n");
  

  thrd_sleep_millisecs(100);

  printf("Thread 2 trying to lock mutex 1\n");
  mtx_lock(&mutex1);
  printf("Thread 2 locked mutex 1\n");

  mtx_unlock(&mutex1);
  mtx_unlock(&mutex2);

  return 0;
}

int main()
{
  thrd_t thread1, thread2;

  mtx_init(&mutex1, mtx_plain);
  mtx_init(&mutex2, mtx_plain);

  thrd_create(&thread1, thread1_func,0);
  thrd_create(&thread2, thread2_func,0);

  thrd_join(thread1,0);
  thrd_join(thread2,0);

  return 0;
}
