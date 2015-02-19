#include<omp.h>
#include<stdio.h>
#include<stdlib.h>

#define N_HILOS 2
#define NUM_ELEMS 20

int main(int argc,char *argv[])
{
	int i,arreglo[NUM_ELEMS];
	for(i=0;i<20;i++)
		arreglo[i]=1;
	omp_set_num_threads(N_HILOS);
	#pragma omp parallel shared(arreglo)
	{
		int i,id_del_hilo,sumap;
		id_del_hilo=omp_get_thread_num();
		if(id_del_hilo==0){
			for(i=0;i<(NUM_ELEMS/N_HILOS);i++)
				sumap+=arreglo[i];
		}	else{
			for(i=(NUM_ELEMS/N_HILOS);i<NUM_ELEMS;i++)
				sumap+=arreglo[i];
		}
		printf("La suma del hilo: %d es %d \n",id_del_hilo,sumap);
	}
	printf("bye!\n");
	return 0;
}

