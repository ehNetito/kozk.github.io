#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

// Creación de una tarea en forma de proceso (programa secuencial)

void main(){
  // Es el proceso principal o padre
  printf("Soy la única tarea del programa, mi PID: %d\n", getpid());
}
