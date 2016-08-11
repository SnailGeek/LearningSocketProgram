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

#include <string.h>

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
	shmid = shm_open("/xyz", O_RDONLY, 0);

	if(shmid == -1)
	  ERR_EXIT("shm_open");
	printf("shm_open_sucess\n");

	
	struct stat buf;
	if(fstat(shmid, &buf) == -1)
	  ERR_EXIT("fstat");

	STU *p;
	p = mmap(NULL, buf.st_size, PROT_READ, MAP_SHARED, shmid, 0);

	if(p == MAP_FAILED)
	  ERR_EXIT("mmap");

	printf("name=%s age=%d\n", p->name, p->age);

	close(shmid);
    return 0;
}
