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

#include <signal.h>

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

size_t size;
mqd_t mqid;
struct sigevent sigev;

void handle_sigusr1(int sig)
{
	mq_notify(mqid, &sigev);

	STU stu;

	unsigned prio;
	if(mq_receive(mqid, (char*)&stu, size, &prio) == (mqd_t)-1)
	  ERR_EXIT("mq_receive");
	printf("name=%s age=%d prio=%u\n", stu.name, stu.age, prio);

}
int main(int argc, char* argv[])		
{

	mqid = mq_open("/abc", O_RDONLY);
	if(mqid == (mqd_t)-1)
	  ERR_EXIT("mq_open");

	struct mq_attr attr;
	mq_getattr(mqid, &attr);
	size = attr.mq_msgsize;

	signal(SIGUSR1, handle_sigusr1);

	sigev.sigev_notify = SIGEV_SIGNAL;
	sigev.sigev_signo = SIGUSR1;
	mq_notify(mqid, &sigev);

	while(1)
	  pause();

	mq_close(mqid);
	return 0;
}
