#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#define N 10
#define VECES 40

/********* Variables globales compartidas ***********/
int buffer[N];
int Frente=0,Posterior=0;
/****************************************************/

/**** Variables globales para la creación de hilos ****/
pthread_t th_prod, th_cons;
/****************************************************/

/**** Variables globales para la creación de semaphore****/
sem_t S_prod, S_cons;
/****************************************************/

void productor(void *ptr);
void consumidor(void *ptr);

int main()
{
     int res, semval;

     pthread_create(&th_prod, NULL,(void *) &productor, (void *) 0);
     pthread_create(&th_cons, NULL,(void *) &consumidor, (void *) 1);

	 sem_init(&S_prod,0,1);
	 sem_init(&S_cons,0,0);
	 
     pthread_join(th_prod,(void *)&res);
     pthread_join(th_cons,(void *)&res);
     return 0;
}

void productor( void *ptr )
{
     int id = (int) ptr;
     int p=0,i;

     printf("Productor id:%d\n",id);
     for(i=0;i<VECES;i++){
        p++;
        buffer[Posterior]=p; //inserta números consecutivos a partir de 1
        Posterior=(Posterior+1)%N;
		sem_post(&S_cons);
     }
     pthread_exit(0);
}

void consumidor( void *ptr )
{
     int id = (int) ptr;
     int prod,i;

     printf("Consumidor id:%d\n",id);
     for(i=0;i<VECES;i++){
	    sem_wait(&S_prod);
        prod= buffer[Frente];
        Frente=(Frente+1)%N;
        printf(" %d ",prod);
		sem_post(&S_prod);
     }
     printf("\n");
     pthread_exit(0);
}


