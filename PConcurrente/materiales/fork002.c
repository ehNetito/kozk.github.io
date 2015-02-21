#include <stdio.h>
#include <sys/types.h>

#define MAX_COUNT 20

void childProcess(void);
void parentProcess(void);

void main(){
  pid_t pid;
  
  pid = fork();
    if(pid == 0)
      childProcess();
    else
      parentProcess();
    
  pause();
}

void childProcess(void){
  int i;
  
  for(i = 1; i <= MAX_COUNT; i++){
    printf("This line is from child %d - value %d - fat %d\n", getpid(), i, getppid());
  }
}

void parentProcess(void){
  int i;
  
  for(i = 1; i <= MAX_COUNT; i++){
    printf("This line is from parent %d - value %d\n", getpid(), i);
  }
  
}

