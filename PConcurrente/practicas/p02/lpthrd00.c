#include <stdio.h>
#include <pthread.h>

// Creación de una tarea en forma de proceso (programa secuencial)
void rutina_hijo();

void main(){
  // Es el proceso principal o padre
  pthread_t h1;
  pthread_create(&h1,NULL, (void *) &rutina_hijo, (void *) NULL);
  printf("Hola hijo\n");
}

void rutina_hijo(){
  printf("Hola padre!\n");
}
