/*OpenMP
Open MultiProcessing
Es una herramienta para explotar el paralelismo en máquinas multiprocesador o SMP.
-Nos apoya en el desarrollo de paralelismo fino o grueso.
- Existe como una librería que puede incluirse en programas hechos en c, c++ o fortran.
- Provee paralelismo en loops.
- Disminuye el uso exl¿plícito del manejo de hilos y su sincronización.

Las directivasopenMP para c, se indican mediante:

#pragma omp
*/
#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#define N 20
#define NHILOS 4

int sumT = 0; //Suma Total
int sumP = 0; // Suma Parcial

void ini_arreglo(int A[N]);
void despl_arreglo(int A[N]);

int main(){
    int A[N];
    ini_arreglo(A);
    despl_arreglo(A);
    omp_set_num_threads(NHILOS); // Cantidad de Hilos
    #pragma omp parallel shared (A)
    {
        int i;
        int id;
        #pragma omp for
            for(i = 0; i < N; i++)
                sumP = sumP + A[i];
        printf(" suma parcial = %d! \n", sumP);
    }
    #pragma omp critical
    {
        sumT = sumT + sumP;
    }
    printf(" suma total = %d! \n", sumT);
    return 0;
}

void ini_arreglo(int A[N]){
    int i;
    for(i = 0; i < N; i++)
        A[i] = 1;
}

void despl_arreglo(int A[N]){
    int i;
    printf("Arreglo :\n");
    for(i = 0; i < N; i++)
        printf(" %d ", A[i]);
    printf("\n");
}

