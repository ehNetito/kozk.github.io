#include<omp.h>
#include<stdio.h>
#include<stdlib.h>

#define N_HILOS 8
#define NUM_ELEMS 160

int main(int argc,char *argv[])
{
	int i,arreglo[NUM_ELEMS],sumap[NUM_ELEMS],total;
	omp_lock_t C1;
	omp_init_lock(&C1);
	srand(time(NULL));
	for(i=0;i<NUM_ELEMS;i++){
		arreglo[i]=rand()%11;
		sumap[i]=0;
	}
	omp_set_num_threads(N_HILOS);
	#pragma omp parallel shared(arreglo)
	{
		int i,id_del_hilo;
		id_del_hilo=omp_get_thread_num();
		int ini=(NUM_ELEMS/N_HILOS)*id_del_hilo;
		int fin=(NUM_ELEMS/N_HILOS)*(id_del_hilo+1);
		for(i=ini;i<fin;i++){
			sumap[id_del_hilo]+=arreglo[i];
		}
		omp_set_lock(&C1);
		total=total+sumap[id_del_hilo];
		omp_unset_lock(&C1);
	}
	for(i=0;i<N_HILOS;i++){
		printf("La suma del hilo: %d es %d \n",i,sumap[i]);
//		total=total+sumap[i];
	}
	printf("Total: %d\n",total);
	printf("bye!\n");
	return 0;
}

