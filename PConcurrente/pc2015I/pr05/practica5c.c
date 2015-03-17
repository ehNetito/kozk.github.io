#include<omp.h>
#include<stdio.h>
#include<stdlib.h>

#define N 1

int i;
int pet=0,rsp=0;
omp_lock_t CS;
omp_lock_t CC;
int id;

void servidor(){
  while(1){
    omp_set_lock(&CS);
    respuesta(pet);
    omp_unset_lock(&CC);
    sleep(1);
  }
}

void clientei(){
    while(1){
	pet=rand()%3;
        printf("Petición=#%d de Proceso: %d\n",pet,id);
        omp_unset_lock(&CS);
        omp_set_lock(&CC);
        sleep(1);
    }
}

void respuesta(int pet){
    ++rsp;
    printf("Respuesta: %d a la Petición=#%d \n",rsp,pet);
}    
    
int main(int argc,char *argv[]){
	int j;
	omp_init_lock(&CS);
	omp_init_lock(&CC);
	omp_set_lock(&CS);
	omp_set_lock(&CC);
	omp_set_num_threads(N+1); // Cantidad de Hilos
	srand(time(NULL));
	#pragma omp parallel shared(pet,i,CC,CS)
	{
		id=omp_get_thread_num();
		if(id==(0)){
		  servidor();
		}
		clientei();
	}
	return 0;
}