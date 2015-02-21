#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>
#include <string.h>

int num_procesos = 3;

void hijo1(int fds[num_procesos]);
void hijoi(int fds[num_procesos], int indice);
void hijo2(int fds[num_procesos], int indice);
 
int main(void)
{
	int ret, i, fds[num_procesos];
 
	if (pipe(fds) == -1) {
		perror("fallo en pipe\n");
		exit(EXIT_FAILURE);
	}
	for (i = 0; i < num_procesos; i++) {
		ret = fork();
		if (ret == 0) {
			/* estamos en alguno de los hijos. */
			switch(i) {
				case 0:
					/* tratamiento hijo 1. */
					hijo1(fds);
					exit(EXIT_SUCCESS);
				case 19:
					/* tratamiento hijo 2. */
					hijo2(fds, i);
					exit(EXIT_SUCCESS);
				default:
				  hijoi(fds, i);
				  exit(EXIT_SUCCESS);
			}
		} else if (ret > 0) {
			/* tratamiento del padre */
//			printf("Padre PID: %d\n", getpid());
//			printf("Introducir hilos a crear: ");
//			scanf(&num_procesos);
			
		} else if (ret == -1) {
			perror("fallo en fork\n");
			exit(EXIT_FAILURE);
		}
	}
        // El padre cierra la tubería antes de esperar y salir
	for(i = 0; i < num_procesos; i++){
	  close(fds[i]);
	}
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

void hijo1(int fds[num_procesos])
{
	int numbytes;
	char buf[4096];
 
	close(fds[0]);
	numbytes = read(STDIN_FILENO, buf, sizeof(buf));
	while (numbytes > 0) {
		if (write(fds[1], buf, strlen(buf)) == -1) {
			perror("fallo en write\n");
			exit(EXIT_FAILURE);
		}
		if (strncmp("fin\n", buf, strlen("fin\n")) == 0)
			break;
		numbytes = read(STDIN_FILENO, buf, sizeof(buf));
	}
	if (numbytes == -1) {
		perror("fallo en read del hijo 1\n");
		exit(EXIT_FAILURE);
	}
	close(fds[1]);
}
 
void hijoi(int fds[num_procesos], int indice)
{
	int numbytes, ind = indice;
	char buf[4096];
	
	close(fds[ind]);
	numbytes = read(fds[ind - 1], buf, sizeof(buf));
	while (numbytes > 0) {
		if (strncmp("fin\n", buf, strlen("fin\n")) == 0)
			break;
		if (write(fds[ind + 1], buf, strlen(buf)) == -1) {
			perror("fallo en write del hijo i\n");
			exit(EXIT_FAILURE);
		}
		numbytes = read(STDIN_FILENO, buf, sizeof(buf));
	}
	if (numbytes == -1) {
		perror("fallo en read del hijo i\n");
		exit(EXIT_FAILURE);
	}
	close(fds[ind]);
}

void hijo2(int fds[num_procesos], int indice)
{
	int numbytes, ind = indice;
	char buf[4096];
 
	close(fds[ind]);
	numbytes = read(fds[ind], buf, sizeof(buf));
	while (numbytes > 0) {
		if (strncmp("fin\n", buf, strlen("fin\n")) == 0)
			break;
 
		if (write(STDOUT_FILENO, buf, strlen(buf)) == -1) {
			perror("fallo en write del hijo 2\n");
			exit(EXIT_FAILURE);
		}
		numbytes = read(fds[0], buf, sizeof(buf));
	}
	if (numbytes == -1) {
		perror("fallo en read del hijo 2\n");
		exit(EXIT_FAILURE);
	}
	close(fds[ind - 1]);
}
