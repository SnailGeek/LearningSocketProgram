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
#include <mqueue.h>
#include <fcntl.h>
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

int main(int argc, char* argv[])		
{

	mqd_t mqid;
	mqid = mq_open("/abc", O_RDONLY);
	if(mqid == (mqd_t)-1)
	  ERR_EXIT("mq_open");


	struct mq_attr attr;
	mq_getattr(mqid, &attr);
	size_t size = attr.mq_msgsize;


	STU stu;
	strcpy(stu.name, "test");
	stu.age = 20;

	unsigned prio;
	if(mq_receive(mqid, (char*)&stu, size, &prio) == (mqd_t)-1)
	  ERR_EXIT("mq_receive");
	printf("name=%s age=%d prio=%u\n", stu.name, stu.age, prio);
	mq_close(mqid);
	return 0;
}
