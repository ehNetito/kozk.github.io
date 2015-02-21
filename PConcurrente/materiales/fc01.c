#include <stdio.h>
#include <unistd.h>

main (void){
	pid_t pid;
	int i, x = 0;

	printf("Soy proceso padre %d\n", getpid());
	printf("Procesos a crear: ");
	scanf("%d", &x);
	printf("\n");

	for(i = 1; i <= x; i++){
		pid = fork();
		if(pid){
			sleep(1);
		}	else{
			printf("Soy hijo %d, mi padre: %d, i: %d\n", getpid(), getppid(), i);
			sleep(1);
			exit(0);
		}
	}
	return(0);
}
