#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

// Creación de una tarea en forma de proceso (programa secuencial)

void main(){
  // Es el proceso principal o padre
  int i;
  pid_t pidh;
  pidh = fork();
  pidh = fork();
  printf("Soy una tarea del programa, mi PID: %d\n", getpid());

}
