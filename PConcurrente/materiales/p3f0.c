#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>
#include <string.h>

int num_procesos = 2;

void hijoi(int ind);

int main(void)
{
	int i, ret;
 
	for (i = 0; i < num_procesos; i++) {
		ret = fork();
		if (ret == 0) {
		  hijoi(i);
			/* estamos en alguno de los hijos. */
			switch(i) {
				case 0:
					/* tratamiento hijo 1. */
					hijoi(i);
					exit(EXIT_SUCCESS);
				case 1:
					/* tratamiento hijo 2. */
					hijoi(i);
					exit(EXIT_SUCCESS);
				default:
				  hijoi(i);
				  exit(EXIT_SUCCESS);
			}
		} else if (ret > 0) {
			/* tratamiento del padre */
//			printf("Padre PID %d, PPID: %d\n", getpid(), getppid());
//			printf("Se crean dos procesos de inicio\n");
hijoi(i);
			ret = wait(NULL);
			while (ret > 0) {
				ret = wait(NULL);
			}
		} else if (ret == -1) {
			perror("fallo en fork\n");
			exit(EXIT_FAILURE);
		}
	}
        // El padre cierra la tubería antes de esperar y salir
	ret = wait(NULL);
	while (ret > 0) {
		ret = wait(NULL);
	}
	/* si hay error, ignoramos si no hay más hijos a esperar. */
	if (ret == -1 && errno != ECHILD) {
		perror("fallo en wait\n");
		exit(EXIT_FAILURE);
	}
}

void hijoi(int ind)
{
  printf("Hijo %d PID %d, PPID: %d", ind, getpid(), getppid());
  _exit(EXIT_SUCCESS);
}
 
