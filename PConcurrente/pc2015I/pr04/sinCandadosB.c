#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#define NHILOS 213

int main (int argc, char *argv[])
{
   int id, suma;

   omp_set_num_threads(NHILOS);

   while(1){
      suma=0;
      #pragma omp parallel private(id) shared(suma)
      {
	  id = omp_get_thread_num();
	  suma=suma + 1;
      }
      if(suma!=213){
          printf("\nbye, suma total=%d, id:%d\n\n",suma,id);
          sleep(1);
      }
      printf("\nbye, suma total=%d, id:%d\n\n",suma,id);
    }
    return 0;
}

