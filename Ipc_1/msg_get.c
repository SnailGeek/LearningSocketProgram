#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#define ERR_EXIT(m)\
do\
{\
	perror(m);\
	exit(EXIT_FAILURE);\
}while(0)

int main(void)
{
	int msgid;
	msgid = msgget(1234, 0666| IPC_CREAT);
	//msgid = msgget(1234, 0666| IPC_CREAT | IPC_EXCL);
	//msgid = msgget(IPC_PRIVATE, 0666| IPC_CREAT | IPC_EXCL);
	//msgid = msgget(IPC_PRIVATE, 0666);
	//msgid = msgget(1234, 0);

	if (msgid == -1)
	  ERR_EXIT("msgget");
	printf("msgget sucess\n");
	printf("msgid=%d\n", msgid);
	return 0;
}
