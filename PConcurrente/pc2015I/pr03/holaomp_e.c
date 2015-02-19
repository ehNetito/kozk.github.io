#include<omp.h>
#include<stdio.h>
#include<stdlib.h>

#define N_HILOS 2
#define NUM_ELEMS 24

int main(int argc,char *argv[])
{
	int i,arreglo[NUM_ELEMS],sumap[NUM_ELEMS];
	for(i=0;i<NUM_ELEMS;i++){
		arreglo[i]=1;
		sumap[i]=0;
	}
	omp_set_num_threads(N_HILOS);
	#pragma omp parallel shared(arreglo)
	{
		int i,id_del_hilo;
		id_del_hilo=omp_get_thread_num();
		if(id_del_hilo==0){
			for(i=0;i<(NUM_ELEMS/N_HILOS);i++)
				sumap[id_del_hilo]+=arreglo[i];
		}	else{
			for(i=(NUM_ELEMS/N_HILOS)*id_del_hilo;i<(NUM_ELEMS/N_HILOS)*(id_del_hilo+1);i++)
				sumap[id_del_hilo]+=arreglo[i];
		}
	}
	for(i=0;i<N_HILOS;i++)
		printf("La suma del hilo: %d es %d \n",i,sumap[i]);
	printf("bye!\n");
	return 0;
}

