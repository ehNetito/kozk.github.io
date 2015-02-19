#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#define NHILOS 213

int main (int argc, char *argv[])
{
  int id, suma;
  omp_lock_t C1;
  omp_init_lock(&C1);
  omp_set_lock(&C1);
  omp_set_num_threads(NHILOS);
  suma=0;
  #pragma omp parallel private(id) shared(suma)
  {
    id = omp_get_thread_num();
    suma=suma + 1;
    omp_unset_lock(&C1);
  }
  printf("\nbye, suma total=%d, id:%d\n\n",suma,id);
  sleep(1);
  return 0;
}

