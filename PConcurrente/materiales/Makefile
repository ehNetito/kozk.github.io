#
# Javier Abellán. 4 de Abril de 2003
#
# Makefile para varios programas de ejemplo de trheads y procesos.
#

# Hacer todos los programas
all : pthread espera pfork sinmutex conmutex pipefork

# programa pfork. Ejemplo de procesos y fork()
pfork : pfork.c
	cc pfork.c -o pfork

pipefork : pipefork.c
	cc pipefork.c -o pipefork

#programa pthread. Ejemplo de thread y pthread_create()
pthread : pthread.c
	cc pthread.c -lpthread -o pthread
	
#programa espera. Ejemplo de thread y pthread_join()
espera : espera.c
	cc espera.c -lpthread -o espera

#programa sinmutex. Ejemplo de colision de thread en un buffer
sinmutex : mutex.c
	cc mutex.c -lpthread -o sinmutex

#programa conmutex. Ejemplo de thread sin colision con pthread_mutex_*()
conmutex : mutex.c
	cc -DMUTEX mutex.c -lpthread -o conmutex
