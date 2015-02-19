#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#define N 20
#define NHILOS 4

int sumT = 0;
void ini_arreglo(int A[N]);
void despl_arreglo(int A[N]);

int main(){
  int A[N];
  ini_arreglo(A);
  despl_arreglo(A);
  omp_set_num_threads(4); // Cantidad de Hilos
  #pragma omp parallel shared (A)
  {

    int i, sum = 0;
    int id;
    int ini;
    int fin;
    int aux = N/NHILOS;
    id = omp_get_thread_num(); // regresa el id del hilo (> 0)
    ini = id * aux;
    fin = id * aux + aux - 1;
    for(i = ini; i <= fin; i++)
      sum = sum + A[i];
    printf(" Hola soy %d, sumo de %d a %d, suma parcial = %d \n", id, ini, fin, sum);
    #pragma omp critical
    {
      sumT = sumT + sum;
    }
  }
  printf(" suma total = %d! \n", sumT);
  return 0;
}

void ini_arreglo(int A[N]){
  int i;
  for(i = 0; i < N; i++)
    A[i] = i + 1;
}

void despl_arreglo(int A[N]){
  int i;
  printf("Arreglo :\n");
  for(i = 0; i < N; i++){
    printf(" %d ", A[i]);
    if(i == 4 || i == 9 || i == 14 || i == 19)
    printf("\n");
  }
}
