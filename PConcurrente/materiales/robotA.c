/* robotA.c */
#include <stdio.h>
#include <stdlib.h>
#include "Semaph.h"
 
void iniciador(void);
 
int main(void)
{
 
        iniciador();
 
	while (1) {
		Semaph_Down(robotA);
		Semaph_Down(excmut);
		produce_pieza_A();
		if (Semaph_Get(prodA) == 0) {
			Semaph_Up(consC);
		}
		Semaph_Up(excmut);
	}
 
}
