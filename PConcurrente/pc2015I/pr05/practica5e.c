#include<omp.h>
#include<stdio.h>
#include<stdlib.h>

#define N 2

int i=0;
int pet=0,rsp=0;
omp_lock_t CS;
omp_lock_t CC;
omp_lock_t CP;
int id;

void servidor(){
  while(1){
    omp_set_lock(&CP);
    rsp=rsp%30;
    omp_unset_lock(&CC);
    omp_set_lock(&CS);
    printf("resp: %d\n",rsp);
    omp_unset_lock(&CP);
    sleep(1);
  }
}

void clientei(){
  while(1){
    omp_set_lock(&CP);
    pet+=pet%3;
    omp_unset_lock(&CS);
    omp_set_lock(&CC);
    printf("Petición=%d de Proceso: %d\n",pet,id);
    omp_unset_lock(&CP);
    sleep(1);
  }
}

int main(int argc,char *argv[]){
	omp_init_lock(&CS);
	omp_init_lock(&CC);
	omp_init_lock(&CP);
	omp_set_lock(&CS);
	omp_set_lock(&CC);
	
	omp_set_num_threads(N); // Cantidad de Hilos
	#pragma omp parallel shared(pet,rsp,i,CC,CS)
	{
		int j=0;
		id=omp_get_thread_num();
		printf("Proceso thread_num: %d\n",id);
		
		clientei();
		if(id==N)
			servidor();
		
	}
	return 0;
}