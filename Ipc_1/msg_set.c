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
	msgid = msgget(1234, 0); 

	if (msgid == -1)
	  ERR_EXIT("msgget");
	printf("msgget sucess\n");
	printf("msgid=%d\n", msgid);

	struct msqid_ds buf;

	msgctl(msgid, IPC_STAT, &buf);
	sscanf("600", "%o", (unsigned int *)&buf.msg_perm.mode);
	msgctl(msgid, IPC_SET, &buf);

	return 0;
}
