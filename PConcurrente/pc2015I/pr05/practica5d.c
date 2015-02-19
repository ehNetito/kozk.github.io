#include<omp.h>
#include<stdio.h>
#include<stdlib.h>

#define N 3

int pet=0;
omp_lock_t CS;
omp_lock_t CC[N];

void servidor(){
  while(1){
    omp_set_lock(&CP);
    x++;
    x=x%100;
    omp_unset_lock(&CC);
   sleep(1);
  }
}

void cliente(){
  while(1){
    omp_set_lock(&CC);
    printf("Producto=#%d\n",x);
    omp_unset_lock(&CP);
    sleep(1);
  }
}

int main(int argc,char *argv[]){
	omp_set_num_threads(N+1); // Cantidad de Hilos
	omp_init_lock(&CP);
	omp_init_lock(&CC);
	
	omp_set_lock(&CS);

	#pragma omp parallel shared(pet,CS,CC)
	{
		printf("Hola Mundo!\n");
	}
	return 0;
}