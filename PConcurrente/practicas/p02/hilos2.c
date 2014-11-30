#include <stdio.h>
#include <pthread.h>

// Creación de una tarea en forma de proceso (programa secuencial)
void rutina_hijo();

void main(){
  // Es el proceso principal o padre
  int i;
  pthread_t h1[4];
  for(i = 0; i < 4; i++){
    pthread_create(&h1[i],NULL, (void *) rutina_hijo, (void *) NULL);
    printf("Hola hijo.\n");
    pthread_join(h1[i], (void *) NULL);
  }
}

void rutina_hijo(){
  printf("Hola padre!, soy %d\n", getpid());
  pthread_exit((void *) NULL);
}
