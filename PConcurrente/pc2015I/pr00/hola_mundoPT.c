#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<time.h>

void imprime();

// Variable Compartida *Los hilos se comunican mediante variables compartidas)
int x=0;

int main(){
  pthread_t t01, t02;
  srand(time(NULL));
  if((pthread_create(&t01, NULL, (void *)&imprime, NULL)) != 0){
    printf("Error en la creaci[on de hilos\n");
    exit(0);
  }
  if((pthread_create(&t02, NULL, (void *)&imprime, NULL)) != 0){
    printf("Error en la creaci[on de hilos\n");
    exit(0);
  }
  pthread_join(t01, NULL);
  pthread_join(t02, NULL);
  return(0);
}

void imprime(){
  int y,i;
  for(i=0; i<5; i++){
    y = x;
    x = x+1;
    sleep(rand()%3);
    printf("El valor anterior de x: %d y el valor actual x: %d \n", y, x);
  }
  pthread_exit(NULL);
}