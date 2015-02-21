#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>

int main(int argc, char *argv[]){
	int ret, i, num_hijos;

	printf("Soy proceso padre PID: %d\n", getpid());
	printf("Escriba cuantos procesos desea crear: ");
	scanf("%d", &num_hijos);

	for(i = 0; i < num_hijos; i++){
		ret = fork();
		if(ret == 0){
			//Es uno de los hijos
			printf("Yo soy el hijo %d, mi pid: %d, pid de padre: %d\n", i, getpid(), getppid());
			exit(EXIT_SUCCESS);
		}  else if(ret == -1){
			perror("Fallo en fork \n");
			exit(EXIT_FAILURE);
		}
	}
	ret = wait(NULL);
	while(ret > 0){
		ret = wait(NULL);
	}
	if(ret == -1 && errno != ECHILD){
		perror("Fallo en wait");
		exit(EXIT_FAILURE);
	}
}
