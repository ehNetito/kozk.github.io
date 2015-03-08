#include<stdio.h>
#include<pthread.h>

#define NH 2

void mensaje(void * ptr){
  int id,dato;
  id=(int)ptr;
  printf("Hola soy %d \n",id);
  printf("Salgo hilo\n");
  pthread_exit((void *)NULL);
}

int main(){
  pthread_t hilos[NH];
  int i,idh;
  for(i=0;i<NH;i++){
    idh=i;
    pthread_create(&hilos[i],NULL,(void *)&mensaje,(void *) idh);
    pthread_join(hilos[i],(void *)NULL);
  }
  return 0;
}