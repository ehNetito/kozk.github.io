/* robotC.c */
#include <stdio.h>
#include <stdlib.h>
#include "Semaph.h"
 
 
int main(void)
{
	iniciador();
 
 
	while (1) {
		Semaph_Down(consC);
		Semaph_Down(consC);
		Semaph_Down(excmut);
		produce_pieza_C();
		Semaph_Up(prodA);
		Semaph_Up(prodA);
		Semaph_Up(prodB);
		Semaph_Up(prodB);
		Semaph_Up(excmut);
	}
}
