#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/mman.h>

#define ERR_EXIT(m)\
do\
{\
	perror(m);\
	exit(EXIT_FAILURE);\
}while(0)

typedef struct stu
{
	char name[32];
	int age;
} STU;

int main(void)
{
	int shmid;
	shmid = shm_open("/xyz", O_CREAT | O_RDWR, 0666);
	if(shmid == -1)
	  ERR_EXIT("shm_open");
	printf("shm_open_sucess\n");

	if(ftruncate(shmid, sizeof(STU)) == -1)
	  ERR_EXIT("ftruncate");
	
	struct stat buf;
	if(fstat(shmid, &buf) == -1)
	  ERR_EXIT("fstat");
	printf("size=%d, mode=%o\n", (int)buf.st_size, buf.st_mode & 07777);

	close(shmid);
    return 0;
}
