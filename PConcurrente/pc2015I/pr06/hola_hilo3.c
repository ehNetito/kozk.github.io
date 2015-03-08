#include<stdio.h>
#include<pthread.h>

#define NH 23

int max=0,dato=0;
pthread_mutex_t CH;

void mensaje(void * ptr){
  int id;
  id=(int)ptr;
  dato=rand()%50;
  pthread_mutex_lock(&CH);
  if(dato>max)
    max=dato;
  pthread_mutex_unlock(&CH);
  printf("Hola soy %d con dato: %d\n",id,dato);
  printf("Salgo max: %d\n",max);
  pthread_exit((void *)NULL);
}

int main(){
  pthread_t hilos[NH];
  int i,idh;
  pthread_mutex_init(&CH,(void *)NULL);
  srand(time(NULL));
  for(i=0;i<NH;i++){
    idh=i;
    pthread_create(&hilos[i],NULL,(void *)&mensaje,(void *) idh);
    pthread_join(hilos[i],(void *)NULL);
  }
  printf("El máximo es: %d\n", max);
  return 0;
}