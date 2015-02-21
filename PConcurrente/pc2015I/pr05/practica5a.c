<<<<<<< HEAD
/*Ejercicio uno corregido*/
=======
/**
Ejercicio uno. Completo
**/
>>>>>>> bd7c2828af859a37564164f9c44ec45daf02b9b9
#include<omp.h>
#include<stdio.h>
#include<stdlib.h>

int idA;
int idB;

void tareaA(){
  printf("Hola soy A, mi id=%d\n",idA);
}
void tareaB(){
  printf("Mucho gusto soy B, mi id=%d\n",idB);
}

int main(int argc,char *argv[]){
<<<<<<< HEAD
=======
	idA=omp_get_thread_num();
	idb=omp_get_thread_num();
	
>>>>>>> bd7c2828af859a37564164f9c44ec45daf02b9b9

	#pragma omp parallel sections
	{
		#pragma omp section
		{
		  idA=omp_get_thread_num();
		  tareaA();
		}
		#pragma omp section
		{
		  idB=omp_get_thread_num();
		  tareaB();
		}
	}
	return 0;
}
