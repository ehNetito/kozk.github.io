/* robotB.c */
#include <stdio.h>
#include <stdlib.h>
#include "Semaph.h"
 
 
int main(void)
{
	iniciador();
 
	while (1) {
		Semaph_Down(robotB);
		Semaph_Down(excmut);
		produce_pieza_B();
		if (Semaph_Get(prodB) == 0) {
			Semaph_Up(consC);
		}
		Semaph_Up(excmut);
	}
 
}
