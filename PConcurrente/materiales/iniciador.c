/* Iniciador.c */
#include <stdio.h>
#include <stdlib.h>
#include "Semaph.h"
 
void iniciador(void){
 
        int prodA = Semaph_Create("robotA", 2);
        if (prodA == -1){
		perror("Fallo al crear semaforo A");
		exit(EXIT_FAILURE);
        }
 
        int prodB = Semaph_Create("robotB", 2); 
        if (prodB == -1){
		perror("Fallo al crear semaforo B");
		exit(EXIT_FAILURE);
	}
 
        int consC = Semaph_Create("robotC", 0);
        if (consC == -1){
		perror("Fallo al crear semaforo C");
		exit(EXIT_FAILURE);
	}
 
        int excmut = Semaph_Create("excmut", 1);
	if (excmut == -1){
		perror("Fallo al crear semaforo exclusion mutua");
		exit(EXIT_FAILURE);
	}
 
}
