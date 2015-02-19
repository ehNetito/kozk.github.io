#include<omp.h>
#include<stdio.h>
#include<stdlib.h>

int idA;
int idB;
int x=0;
omp_lock_t CP;
omp_lock_t CC;

void productor(){
  while(1){
    omp_set_lock(&CP);
    x++;
    x=x%100;
    omp_unset_lock(&CC);
    sleep(1);
  }
}

void consumidor(){
  while(1){
    omp_set_lock(&CC);
    printf("Producto=#%d\n",x);
    omp_unset_lock(&CP);
    sleep(1);
  }
}

int main(int argc,char *argv[]){
	omp_init_lock(&CP);
	omp_init_lock(&CC);
	
	omp_set_lock(&CC);

	int idA=omp_get_thread_num();
	int idb=omp_get_thread_num();
	
	#pragma omp parallel sections shared(x)
	{
		#pragma omp section
		  productor();
		#pragma omp section
		  consumidor();
	}
	return 0;
}