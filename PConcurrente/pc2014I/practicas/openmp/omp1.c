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

int main(){
    omp_set_num_threads(4); // Cantidad de Hilos
    #pragma omp parallel
    {
        printf("Hola! \n");
    }
    return 0;
}

