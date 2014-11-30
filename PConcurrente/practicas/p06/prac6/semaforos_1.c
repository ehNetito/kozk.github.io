#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>


sem_t S;  //declaración del semáforo S

int main(){
    int valsem,i;
    sem_init(&S,0,3); //inicialización del semáforo S = 3
    for(i = 0; i < 3; i++){
        wait(&S);
        sem_getvalue (&S,&valsem); //obtengo el valor actual de S
        printf("Valor de S= %d\n",valsem);
    }
    exit(0);
}


