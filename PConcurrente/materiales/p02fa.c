#include <stdio.h>
#include <string.h>
#include <sys/types.h>

#define MAX_COUNT 20
#define BUF_SIZE 10

void main(){
    pid_t pid;
    int i;
    char buf[BUF_SIZE];

    fork();
    pid = getpid();
    for(i = 1; i <= MAX_COUNT; i++){
        sprintf(buf, "This pid = %d, value = %d\n", pid, i);
        printf("this pid %d and value %d and ppid %d\n", pid, i, getppid());
        write(1, buf, strlen(buf));
    }
} 
