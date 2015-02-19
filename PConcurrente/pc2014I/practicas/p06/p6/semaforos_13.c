#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>

/********* Declaración de un semáforo **************/
sem_t S;  //declaración del semáforo S
/****************************************************/

int main()
{
   int valsem;

   sem_init(&S,3,0); //inicialización del semáforo S = 3
   sem_getvalue (&S,&valsem); //obtengo el valor actual de S
   printf("Valor de S= %d\n",valsem);
   sem_post(&S);
   sem_getvalue (&S,&valsem); //obtengo el valor actual de S
   printf("Valor de S= %d\n",valsem);
   sem_post(&S);
   sem_getvalue (&S,&valsem); //obtengo el valor actual de S
   printf("Valor de S= %d\n",valsem);
   sem_post(&S);
   sem_getvalue (&S,&valsem); //obtengo el valor actual de S
   printf("Valor de S= %d\n",valsem);

   exit(0);
}


