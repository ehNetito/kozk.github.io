#ifndef _LIBSEM_H_
#define _LIBSEM_H_

int Semaph_Create(char *nombre, int valor);
void Semaph_Destroy(char *nombre, int semid);
int Semaph_Down(int semid);
int Semaph_Up(int semid);
int Semaph_Get(int semid);

#endif
