#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#define N 10
#define VECES 40

int buffer[N];
int Frente=0,Posterior=0;

sem_t semvacias; // semaforo productor
sem_t semllenas; // semaforo consumidor


void productor(void * ptr);
void consumidor(void * ptr);

int main(){
    pthread_t th_prod, th_cons;
    int res;

    sem_init(&semvacias, 0, N); //inicialización del semáforo productor
    sem_init(&semllenas, 0, 0); //inicialización del semáforo consumidor

    pthread_create(&th_prod, NULL,(void *) &productor, (void *) 0);
    pthread_create(&th_cons, NULL,(void *) &consumidor, (void *) 1);
 
    pthread_join(th_prod,(void *)&res);
    pthread_join(th_cons,(void *)&res);
    return 0;
}

void productor( void *ptr ){
    int id = (int) ptr;
    int p=0,i;
    printf("Productor id:%d\n",id);
    for(i=0;i<VECES;i++){
        sem_wait(&semvacias);
        p++;
        buffer[Posterior]=p;
        Posterior=(Posterior+1)%N;
        sem_post(&semllenas);
    }
    pthread_exit(0);
}

void consumidor( void *ptr ){
    int id = (int) ptr;
    int prod,i;

    printf("Consumidor id:%d\n",id);
    for(i=0;i<VECES;i++){
        sem_wait(&semllenas);
        prod= buffer[Frente];
        Frente=(Frente+1)%N;
        printf(" %d ",prod);
        sem_post(&semvacias);
    }
    printf("\n");
    pthread_exit(0);
}


