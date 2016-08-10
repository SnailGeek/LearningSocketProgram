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

#define ERR_EXIT(m)\
do\
{\
	perror(m);\
	exit(EXIT_FAILURE);\
}while(0)

int main(void)
{
	mqd_t mqid;
	mqid = mq_open("/abc", O_CREAT | O_RDWR, 0666, NULL);
	if(mqid == (mqd_t)-1)
	  ERR_EXIT("mq_open");

	printf("mq_open success\n");
	mq_close(mqid);
	return 0;
}
