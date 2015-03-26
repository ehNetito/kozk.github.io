// Por iniciar 
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#define NSALIDAS 10
#define SENTRADAS 10
#define NLUGARES 24
#define NCOCHES 26

sem_t SEntrada;
pthread_mutex_t C1;
char est[NLUGARES];
int lugar;

void automovil( void *id );
void entrada( void *id );
void salida( void *id );
void interfaz();

int main()
{
	int i;
	for(i=0;i<24;i++)
	{
		est[i]=' ';
	}
	sem_init( &SEntrada,0,24);
	pthread_t th_automovil,th_automovil2;
	pthread_mutex_init(&C1,NULL);

	int res;
	lugar = 0;
	
	pthread_create( &th_automovil2, NULL,(void *) &automovil, (void *) 1);
    pthread_create( &th_automovil, NULL,(void *) &automovil, (void *) 0);
	pthread_join(th_automovil,(void *)&res);
	pthread_join(th_automovil2,(void *)&res);
	return 0;
}

void automovil( void *id ){
	int ent,tie,sal;
	ent = rand()%NSALIDAS;
	tie = rand();
	sal = rand()%NSALIDAS;
	int i;
	for(i=0;i<NCOCHES;i++)
	{
		interfaz();
		entrada(id);
		sleep(1);
		salida(id);
	}
}


void entrada( void *id )
{
	int ident = (int) id;
	char ident2 = (char) ident;
	sem_wait(&SEntrada);
	pthread_mutex_lock(&C1);
	est[lugar] = '1';
	lugar = (lugar+1)%24;
	pthread_mutex_unlock(&C1);

}


void salida( void *id )
{
	est[lugar] = '@';
	sem_post(&SEntrada);
}


void interfaz()
{
	printf("|%c|%c|%c|%c|%c|%c|%c|%c|\n|%c|%c|%c|%c|%c|%c|%c|%c|\n|%c|%c|%c|%c|%c|%c|%c|%c|\n#################\n"
		    ,est[0],est[1],est[2],est[3],est[4],est[5],est[6],est[7]
		    ,est[8],est[9],est[10],est[11],est[12],est[13],est[14],est[15]
		    ,est[16],est[17],est[18],est[19],est[20],est[21],est[22],est[23]);
}


// En la wiki podemos agregar la info para el reporte
