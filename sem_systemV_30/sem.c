#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <string.h>

#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>

union semun {
	int val;    /* Value for SETVAL */
	struct semid_ds *buf;    /* Buffer for IPC_STAT, IPC_SET */
	unsigned short  *array;  /* Array for GETALL, SETALL */
	struct seminfo  *__buf;  /* Buffer for IPC_INFO(Linux-specific) */
};


#define ERR_EXIT(m)\
do\
{\
	perror(m);\
	exit(EXIT_FAILURE);\
}while(0)


typedef struct stu
{
	int age;
	char name[32];
} STU;


int sem_create(key_t key)
{
	int semid;
	semid = semget(key, 1, IPC_CREAT | IPC_EXCL | 0666);
	if(semid == -1)
	  ERR_EXIT("semget");
	return semid;
}

int sem_open(key_t key)
{
	int semid;
	semid = semget(key, 0, 0);
	if( semid == -1)
	  ERR_EXIT("semget");

	return 0;
}

int sem_setval(int semid, int val)
{
	union semun su;
	su.val = val;
	int ret;
	ret = semctl(semid, 0, SETVAL, su);
	if(ret == -1)
	  ERR_EXIT("semctl");
	return 0;
}

int sem_getval(int semid)
{
	int ret;
	ret = semctl(semid, 0, GETVAL, 0);
	if(ret == -1)
	  ERR_EXIT("sem_getval");
	return ret;
}

int sem_d(int semid)
{
	int ret;
	ret = semctl(semid, 0, IPC_RMID, 0);
	if(ret == -1)
	  ERR_EXIT("semctl_rmid");

	return 0;
}

int sem_p(int semid)
{
	struct sembuf sb = {0, -1, 0};
	int ret;
	ret = semop(semid, &sb, 1);
	if(ret == -1)
	  ERR_EXIT("semop");
	return 0;
}
int sem_v(int semid)
{
	struct sembuf sb = {0, 1, 0};
	int ret;
	ret = semop(semid, &sb, 1);
	if(ret == -1)
	  ERR_EXIT("semop");
	return 0;
}

int main(int argc, char* argv[])
{
	int semid;
	semid = sem_create(1234);
	sleep(5);

	sem_d(semid);
	return 0;
}
