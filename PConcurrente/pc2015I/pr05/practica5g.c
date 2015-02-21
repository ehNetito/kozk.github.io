#include<omp.h>
#include<stdio.h>
#include<stdlib.h>

#define N 1

int pet=0;
int rsp=0;
omp_lock_t CS;
omp_lock_t CC;

void servidor(){
  while(1){
    omp_set_lock(&CS);
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

    printf("Soy servidor con petición: %d y respuesta: %d\n",pet,rsp);
    omp_unset_lock(&CC);
    sleep(1);
  }
}

void cliente(){
  while(1){
    omp_set_lock(&CC);
    pet++;
    pet=pet%3;
    int id=omp_get_thread_num();
    printf("Petición: %d, del cliente con id= %d\n",pet,id);
    omp_unset_lock(&CS);
    sleep(1);
  }
}

int main(int argc,char *argv[]){
	omp_init_lock(&CS);
	omp_init_lock(&CC);
	
	omp_set_lock(&CC);
	omp_set_num_threads(N+1);
	#pragma omp parallel shared(pet,rsp,CS,CC)
	{
		int id=omp_get_thread_num();
		if(id==0)
			servidor();
		cliente();
	}
	return 0;
}