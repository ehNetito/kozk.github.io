all:
	gcc -I. -c libsem.c -o libsem.o
	gcc -I. -c test/semaforo_test_consumidor.c -o semaforo_test_consumidor.o
	gcc -I. -c test/semaforo_test_productor.c -o semaforo_test_productor.o
	gcc -I. libsem.o semaforo_test_productor.o -o test_productor
	gcc -I. libsem.o semaforo_test_consumidor.o -o test_consumidor

clean:
	rm -rf *.o test_productor test_consumidor
