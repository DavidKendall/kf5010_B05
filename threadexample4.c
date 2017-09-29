#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <assert.h>
#include <sched.h>

#define N_THREADS 5
char *messages[N_THREADS] = {
  "Hello world",
  "Good golly Miss Molly",
  "I've got stones in my passway",
  "Give me red lipstick",
  "No country for old men"
};

void *printMessage(void *arg) {
  int i;
  long tid = (long)arg;

  for (i = 0; i < 100; i += 1) {
    printf("Thread %ld: %s\n", tid, messages[tid]);
    pthread_yield();
  }
  printf("Thread %ld finished\n", tid);
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

