/**
Ejercicio uno. Completo
**/
#include<omp.h>
#include<stdio.h>
#include<stdlib.h>

int idA;
int idB;

void tareaA(){
  printf("Hola soy A, mi id=#%d\n",idA);
}
void tareaB(){
  printf("Mucho gusto soy B, mi id=#%d\n",idB);
}

int main(int argc,char *argv[]){
	idA=omp_get_thread_num();
	idb=omp_get_thread_num();
	

	#pragma omp parallel sections
	{
		#pragma omp section
		  tareaA();
		#pragma omp section
		  tareaB();
	}
	return 0;
}
