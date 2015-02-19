/*Ejercicio uno corregido*/
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