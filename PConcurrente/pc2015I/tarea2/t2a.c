#include<omp.h>
#include<stdio.h>
#include<stdlib.h>

#define N 3

int pet=0;
int rsp=0;
omp_lock_t CP;
omp_lock_t CC;
omp_lock_t CD;

void productor(){
  int id=omp_get_thread_num();
  while(1){
    omp_set_lock(&CP);
    printf("----Productor %d con petición: %d\n",id,pet);
    if(pet==0){
      rsp=rsp%10;
      rsp++;
    }	else if(pet==1){
      rsp=(rsp%10)+10;
      rsp++;
    }	else if(pet==2){
      rsp=(rsp%10)+20;
      rsp++;
    }
    omp_unset_lock(&CD);
    printf("----Productor %d con respuesta: %d\n",id,rsp);
    sleep(1);
  }
}

void distribuidor(){
  int id=omp_get_thread_num();
  while(1){
    omp_set_lock(&CD);
    printf("--Distribuidor: %d, Petición = %d\n",id,pet);
    omp_unset_lock(&CP);
    omp_set_lock(&CD);
    printf("--Distribuidor: %d, Respuesta = %d\n",id,rsp);
    omp_unset_lock(&CC);

    sleep(1);
  }
}

void consumidor(){
  int id=omp_get_thread_num();
  while(1){
    pet++;
    pet=pet%3;
    printf("Cliente con id= %d, Petición: %d\n",id,pet);
    omp_unset_lock(&CD);
    omp_set_lock(&CC);
    printf("Cliente pido= %d, Recibo: %d\n",pet,rsp);
    sleep(1);
  }
}

int main(int argc,char *argv[]){
	omp_init_lock(&CP);
	omp_init_lock(&CC);
	omp_init_lock(&CD);
	
	omp_set_lock(&CP);
	omp_set_lock(&CD);
	omp_set_lock(&CC);
	omp_set_num_threads(N);
	#pragma omp parallel shared(pet,rsp,CP,CC,CD)
	{
		int id=omp_get_thread_num();
		if(id==0)
			consumidor();
		else if(id==1)
			distribuidor();
		else if(id==2)
			productor();
	}
	return 0;
}