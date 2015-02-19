#include<omp.h>
#include<stdio.h>
#include<stdlib.h>

int main(int argc,char *argv[])
{
	int id_del_hilo;
	#pragma omp parallel
	{
		id_del_hilo=omp_get_thread_num();
		printf("Hello World soy Gabriel nUmero de hilo: %d\n",id_del_hilo);
	}
	printf("bye!\n");
	return 0;
}

