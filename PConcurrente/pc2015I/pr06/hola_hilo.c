#include<stdio.h>
#include<pthread.h>

void mensaje(void * ptr){
  int id,dato;
  id=(int)ptr;
  printf("Hola soy %d \n",id);
  printf("Salgo hilo\n");
  pthread_exit((void *)NULL);
}

int main(){
  pthread_t hilo1;
  int idh;
  idh=1;
  pthread_create(&hilo1,NULL,(void *)&mensaje,(void *) idh);
  pthread_join(hilo1,(void *)NULL);
  return 0;
}