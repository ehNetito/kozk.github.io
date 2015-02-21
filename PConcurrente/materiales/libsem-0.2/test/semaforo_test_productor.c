#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>

#include "libsem.h"

int i = 0;

void escribe()
{
	int fd;
	char *mensaje[] = {"1", "2", "3"};

	fd = open("datos.txt", O_CREAT | O_TRUNC | O_WRONLY, 0600);
	if (fd == -1) {
		perror("open");
		return;
	}
	/* escribe un texto en el fichero */
	if (write(fd, mensaje[i], strlen(mensaje[i])) == -1) {
		perror("write");
		return;
	}
	printf("Mensaje `%s' insertado en datos.txt\n", mensaje[i]);
	if (++i == 3)
		i = 0;

	close(fd);
}

int main()
{
	int sem_ocu, sem_lib, sem_exc;

	sem_exc = Semaph_Create("exc", 1);
	if (sem_exc == -1) {
		perror("semaph_create");
		exit(EXIT_FAILURE);
	}

	sem_lib = Semaph_Create("lib", 1);
	if (sem_lib == -1) {
		perror("semaph_create");
		exit(EXIT_FAILURE);
	}

	sem_ocu = Semaph_Create("ocu", 0);
	if (sem_lib == -1) {
		perror("semaph_create");
		exit(EXIT_FAILURE);
	}

	for(;;) {
		Semaph_Down(sem_lib);
		Semaph_Down(sem_exc);
		escribe();
		Semaph_Up(sem_exc);
		Semaph_Up(sem_ocu);

		/* 
		 * Este sleep() unicamente sirve para poder 
		 * observar la evolucion de los semaforos
		 */
		//sleep(1);
	}
}
