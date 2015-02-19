#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

// Creación de una tarea en forma de proceso (programa secuencial)

void main(){
  // Es el proceso principal o padre
  pid_t pidh;
  printf("Soy padre: %d, mi hijo: %d\n", getppid(), getpid());
  printf("Soy hijo: %d, mi´padre: %d\n", getpid(), getppid());
}

