#include<omp.h>
#include<stdio.h>
#include<stdlib.h>

#define N 1

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
	omp_set_num_threads(N+1);
	#pragma omp parallel shared(x)
	{
		int id=omp_get_thread_num();
		if(id==0)
			productor();
		consumidor();
	}
	return 0;
}