#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>

#include "libsem.h"

void leer()
{
	int fd, numbytes;
	char buf[16];

	fd = open("datos.txt", O_RDONLY, 0400);
	if (fd == -1) {
		perror("open");
		return;
	}

	if ((numbytes = read(fd, buf, sizeof(buf))) == -1) {
		perror("read");
		return;
	}
	close(fd);
	
	buf[numbytes] = '\0';

	printf("Consumidor: %s\n", buf);
}

int main()
{
	int sem_lib, sem_ocu, sem_exc;

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
		Semaph_Down(sem_ocu);
		Semaph_Down(sem_exc);
		leer();
		Semaph_Up(sem_exc);
		Semaph_Up(sem_lib);

		/*
		 * Este sleep() unicamente sirve para poder
		 * observar la evolucion de los semaforos
		 */
		//sleep(1);
	}
}
