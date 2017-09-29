#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

int globvar = 6;

void *threadController(void *arg) {
      globvar++; 
      // var++; Notice this variable is not accessible
      printf("New thread : pid = %d, tid = 0x%lx, globvar = %d, "
              "var = %s\n", getpid(), (unsigned long)pthread_self(),
              globvar, "Not accessible");
      pthread_exit((void *)0);
}

int main(void) {
  int var = 88;
  pthread_t thread;

  printf("before thread create\n");
  if (pthread_create(&thread, NULL, threadController, NULL) != 0) {
      fprintf(stderr, "thread create failed\n");
      exit(-1);
  } else {
      pthread_join(thread, NULL); // main thread
      printf("Main thread: pid = %d, tid = 0x%lx, globvar = %d, " 
             "var = %d\n", getpid(), (unsigned long)pthread_self(),
              globvar, var);
  }
  exit(0);
}

