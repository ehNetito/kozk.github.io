#include<omp.h>
#include<stdio.h>
#include<stdlib.h>

#define N 7

int pet=0,prd=0;
omp_lock_t CS; // Servidor
omp_lock_t CC; // CLiente
omp_lock_t CP; // Petición

int produce(int pet){
    ++prd;
    if(pet==0){
      prd=prd%10;
      prd++;
    }	else if(pet==1){
      prd=(prd%10)+10;
      prd++;
    }	else if(pet==2){
      prd=(prd%10)+20;
      prd++;
    }

    printf("Respuesta: %d a la Petición = %d \n",prd,pet);
    return prd;
}

void servidor(){
  while(1){
//     omp_set_lock(&CP);
    omp_set_lock(&CS);
    prd=produce(pet);
    omp_unset_lock(&CC);
//     printf("resp: %d\n",prd);
//     omp_unset_lock(&CP);
    sleep(1);
  }
}

void clientei(){
  while(1){
    omp_set_lock(&CP);  // Petición
    pet=(pet+1)%3;
    printf("Petición = %d de Proceso: %d\n",pet,omp_get_thread_num());
    omp_unset_lock(&CS); // Servidor
    omp_set_lock(&CC); // Cliente
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
	
	omp_set_num_threads(N+1); // Cantidad de Hilos
	#pragma omp parallel shared(pet,prd,CC,CS,CP)
	{
		int id=omp_get_thread_num();
		if(id==0)
			servidor();
		clientei();
		
	}
	return 0;
}