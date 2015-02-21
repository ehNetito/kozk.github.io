#include <stdio.h>
#include <string.h>
#include <sys/types.h>

#define MAX_COUNT 20
#define BUF_SIZE 10

void main(){
    pid_t pid, ppid;
    int i=0, estado;
    ppid = getppid();
//    do{
      fork();
      pid = getpid();
      switch(pid){
        case -1: 
          perror("no se pudo crear el hijo");
          break;
        case 0: 
          printf("This pid = %d, value = %d\n", pid, i);
          break;
        default: 
          if(pid == ppid){
            printf("This ppid = %d, value = %d\n", ppid, i);
          }  else{
//            exit(i);
          }
      }
      i++;
//    }  while(i < 10);
} 
