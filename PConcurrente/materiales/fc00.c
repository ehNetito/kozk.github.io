#include <stdio.h>
#include <unistd.h>

main (void){
	pid_t pid;
	int x;

		for(x = 1; x <= 20; x++){
		pid = fork();
		if(pid){
			printf("Soy proceso %d, i: %d\n", getpid(), x);
			sleep(2);
		}	else{
			printf("Soy hijo %d, mi padre: %d, i: %d\n", getpid(), getppid(), x);
			sleep(2);
			exit(0);
		}
	}
	return(0);
}
