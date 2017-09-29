#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <assert.h>

#define N_THREADS 5

void *printMessage(void *arg) {
  int i;

  for (i = 0; i < 100; i += 1) {
    printf("This is a message from thread %ld\n", (long)arg);
  }
  printf("Thread %ld finished\n", (long)arg);
  pthread_exit((void *)0);
}

int main(void) {
  pthread_t thread[N_THREADS];
  int rc;
  long i;

  for (i = 0; i < N_THREADS; i += 1) {
    rc = pthread_create(&thread[i], NULL, printMessage, (void *)i);
    assert(rc == 0);
  }

  for (i = 0; i < N_THREADS; i += 1) {
    rc = pthread_join(thread[i], NULL);
    assert(rc == 0);
  }
  printf("Finished\n");
  exit(0);
}
