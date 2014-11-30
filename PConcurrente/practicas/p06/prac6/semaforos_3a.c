#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#define N 5

int Frente=0,Posterior=0;

sem_t semten[N]; // semaforo productor
sem_t semllenas; // semaforo consumidor


void productor(void * ptr);
void consumidor(void * ptr);
void filosofo(void * ptr);

int main(){
    int i, res;
    pthread_t th[i];

    for(i = 0; i < N; i++)
        sem_init(&semten[i], 0, 1); //inicialización del semáforo productor
    for(i = 0; i < N; i++)
        pthread_create(&th[i], NULL,(void *) &filosofo, (void *) 0);
    for(i = 0; i < N; i++)
        pthread_join(th[i],(void *)&res);
    return 0;
}

void filosofo(void * ptr){
    int i;
    int id = (int) ptr;
    while(1){
        piensa(id);
        if(id > 0){
            sem_wait(&semten[(i + 1)%N]);
            sem_wait(&semten[i]);
        }
        sem_wait(&semten[i]);
        sem_wait(&semten[i + 1]);
        come(id);
        sem_post(&semten[id]);
        sem_post(&semten[id + 1]);
    }
}

void piensa(int idm){
    printf("Soy filósofo id:%d pienso\n",idm);
}

void come(int idm){
    printf("Soy filósofo id:%d como\n",idm);
}


