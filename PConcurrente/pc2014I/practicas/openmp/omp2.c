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

void ini_arreglo(int A[N]){
    int i;
    for(i = 0; i < N; i++)
        A[i] = i;
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
        printf("Hola soy %d, sumo de %d a %d, suma = %d! \n", id, ini, fin, sum);
    }
    return 0;
}

