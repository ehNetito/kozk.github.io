#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <errno.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int Semaph_Create(char *nombre, int valor)
{
	int nuevo = 1;
	int fd, semid;
	key_t key;
	union semun {
		int val;
	} arg;
	char buf[FILENAME_MAX];

	sprintf(buf, "/tmp/%s", nombre);

	fd = open(buf, O_CREAT | O_EXCL | O_TRUNC, 0400);
	if (fd == -1) {
		if (errno != EEXIST) {
			perror("open");
			return -1;
		}
		/* semaforo ya existente */
		nuevo = 0;
	}
	close(fd);

	key = ftok(buf, 1);
	if (key == -1) {
		perror("ftok");
		return -1;
	}

	semid = semget(key, 1, IPC_CREAT | 0600);
	if (semid == -1) {
		perror("semget");
		return -1;
	}

	if (nuevo) {
		arg.val = valor;
		if (semctl(semid, 0, SETVAL, arg) == -1) {
			perror("semctl");
			return -1;
		}
	}

	return semid;
}

void Semaph_Destroy(char *nombre, int semid)
{
	char buf[FILENAME_MAX];

	snprintf(buf, FILENAME_MAX, "/tmp/%s", nombre);

	if (unlink(buf) == -1)
		perror("unlink");

	if (semctl(semid, 0, IPC_RMID) == -1)
		perror("semctl");
}

int Semaph_Down(int semid)
{
	struct sembuf buf = { 0, -1, 0 };

	if (semop(semid, &buf, 1) == -1) {
		perror("semop");
		return -1;
	}
	return 0;
}

int Semaph_Up(int semid)
{
	struct sembuf buf = { 0, 1, 0 };

	if (semop(semid, &buf, 1) == -1) {
		perror("semop");
		return -1;
	}
	return 0;
}

int Semaph_Get(int semid)
{
	return semctl(semid, 0, GETVAL);
}
