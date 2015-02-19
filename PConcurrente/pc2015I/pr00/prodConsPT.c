#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<time.h>

#define TAM 20
#define VERDADERO 1
#define FALSO 0

void consumidor();
void productor();

int buffer[TAM];

int main(){
  pthread_t t01, t02;
  int i;
  srand(time(NULL));
  for(i=0;i<TAM;i++)
    buffer[i]=-1;
  if((pthread_create(&t01, NULL, (void *)&consumidor, NULL)) != 0){
    printf("Error en la creaci[on de hilos\n");
    exit(0);
  }
  if((pthread_create(&t02, NULL, (void *)&productor, NULL)) != 0){
    printf("Error en la creaci[on de hilos\n");
    exit(0);
  }
  pthread_join(t01, NULL);
  pthread_join(t02, NULL);
  return(0);
}

void productor(){
  int y,entrada=0;
  while(VERDADERO){
    buffer[entrada]=rand()%3;
    entrada = (entrada+1)%TAM;
    printf("Se produce DATO: %d \n", buffer[entrada-1]);
    sleep((rand()%3)+1);
  }
//  pthread_exit(NULL);
}

void consumidor(){
  int y,salida=0;
  while(VERDADERO){
    y = buffer[salida];
    salida = (salida+1)%TAM;
    printf("Se consume DATO: %d \n", y);
    sleep((rand()%3)+1);
  }
//  pthread_exit(NULL);
}