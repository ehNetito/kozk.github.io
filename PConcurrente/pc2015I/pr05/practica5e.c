#include<omp.h>
#include<stdio.h>
#include<stdlib.h>

#define N 1

int pet=0,rsp=0;
omp_lock_t CS;
omp_lock_t CC[N];

void servidor();
void clientei();

int main(int argc,char *argv[]){
	int i=0,j=0;
	omp_init_lock(&CS);
	omp_init_lock(&CC[i]);

77	omp_set_lock(&CS);
77	omp_set_lock(&CC[i]);
	
	omp_set_num_threads(N+1); // Cantidad de Hilos
	#pragma omp parallel shared(pet,rsp,i,CC[i],CS)
	{
		int id;
		id=omp_get_thread_num();
		printf("Proceso id: %d\n",id);
		for(0)
			clientei();
		else
			servidor();
		
		#pragma critical
		{
			pet=pet%3;
			pet++;
			rsp=rsp%3;
			rsp++;
		}
	}
	return 0;
}

void servidor(){
  while(1){
    omp_set_lock(&CS);
    rsp=rsp%10;
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
