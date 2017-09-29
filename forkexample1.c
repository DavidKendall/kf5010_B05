#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>

int globvar = 6;

int main(void) {
  int var = 88;
  pid_t pid;

  printf("before fork\n");
  if ((pid = fork()) < 0) {
      fprintf(stderr, "fork failed\n");
      exit(-1);
  } else if (pid == 0) {
      globvar++; //child
      var++;
      printf("Child : pid = %d, globvar = %d, var = %d\n",
               getpid(), globvar, var);
  } else {
      waitpid(pid, NULL, 0); // parent
      printf("Parent: pid = %d, globvar = %d, var = %d\n",
               getpid(), globvar, var);
  }
  exit(0);
}

