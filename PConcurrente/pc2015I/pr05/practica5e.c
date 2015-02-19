#include<omp.h>
#include<stdio.h>
#include<stdlib.h>

#define N 2

int i;
int pet=0,rsp=0;
omp_lock_t CS;
omp_lock_t CC;
int id;
void servidor(){
  while(1){
    omp_set_lock(&CS);
    rsp=rsp%30;
    printf("resp: %d\n",rsp);
    omp_unset_lock(&CC);
    sleep(1);
  }
}

void clientei(){
  while(1){
    omp_unset_lock(&CS);
    printf("Petición=#%d de Proceso: %d\n",pet,id);
    omp_set_lock(&CC);
    sleep(1);
  }
}

int main(int argc,char *argv[]){
	int j;
	omp_init_lock(&CS);
	omp_init_lock(&CC);
	omp_set_lock(&CS);

	omp_set_num_threads(N); // Cantidad de Hilos
	
	omp_set_lock(&CC);
	#pragma omp parallel shared(pet,rsp,i,CC,CS)
	{
		id=omp_get_thread_num();
		printf("Proceso id: %d\n",id);
		if(id=0)
			clientei();
		else
			servidor();
		
		#pragma critical
		{
			i=i%2;
			i++;
			pet++;
			pet=pet%100;
		}
	}
	return 0;
}