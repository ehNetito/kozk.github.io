#include <stdio.h>
#include <stdlib.h>
#include "pthread.h"

#define N 3
#define MAX 200

int ca = 0;
int ce = 0;
int ci = 0;
int co = 0;
int cu = 0;
int c;
FILE * fp;
pthread_t h[N];
pthread_mutex_t candl;
pthread_mutex_t cande;

int cuentaLineas();
void contador(void * ptr);

int main(int argc, char **argv){
    int i;
    int lin = 0;
    char *nomarch;
    char buffer[MAX];
    nomarch = argv[1];
    fp = fopen(nomarch, "r");
    pthread_t h[N];
    if(fp == NULL){
        printf("no se pudo abrir el archivo %s\n", nomarch);
        exit(1);
    }
	lin = cuentaLineas();
    printf(" <lin>: %d\n", lin);
    fflush(fp);
    pthread_mutex_init(&cande, NULL);
    for(i = 0; i < N; i++){
        pthread_create(&h[i], NULL, (void *) contador, &i);
    }
    for(i = 0; i < N; i++){
        pthread_join(h[i], NULL);
    }
    printf("-- fin\n");
    fclose(fp);
    printf("totales: ca: %d, ce %d, ci %d, co %d, cu %d\n", ca, ce, ci, co, cu);
    return 0;
}

void contador(void * ptr){
    int id = (int) ptr;
    int aes = 0;
    int ees = 0;
    int ies = 0;
    int oes = 0;
    int ues = 0;
    c = fgetc(fp);
    while(!feof(fp) || c != '\n'){
        if(c == 'a' || c == 'A')
            aes++;
        else if(c == 'e' || c == 'e')
            ees++;
        else if(c == 'i' || c == 'I')
            ies++;
        else if(c == 'o' || c == 'O')
            oes++;
        else if(c == 'u' || c == 'U')
            ues++;
        else{
        }
        c = fgetc(fp);
    }
    pthread_mutex_lock(&cande);
    ca = ca + aes;
    ce = ce + ees;
    ci = ci + ies;
    co = co + oes;
    cu = cu + ues;
    pthread_mutex_unlock(&cande);
    printf("Hilo: %d: ca: %2d, ce %2d, ci %2d, co %2d, cu %2d\n", id, ca, ce, ci, co, cu);
    pthread_exit(&h[id]);
}
