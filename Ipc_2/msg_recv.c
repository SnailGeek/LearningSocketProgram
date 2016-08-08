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

struct msgbuf{
	long mtype;
	char mtext[1];
};

#define MSGMAX 8192

int main(int argc, char *argv[])
{
	int flag = 0;
	int type = 0;
	char opt;
	while(1){
		opt = getopt(argc, argv, "nt:");
		if(opt == '?')
		  exit(EXIT_FAILURE);
		if(opt == -1)//所有的参数都解析完毕
		  break;
		switch(opt){
			case 'n':
				//printf("AAA\n");
				flag |= IPC_NOWAIT;
				break;
			case 't':
				/*
				printf("bbb\n");
				int n = atoi(optarg);
				printf("n=%d\n",n);
				break;*/
				type = atoi(optarg);
				break;
		}
	}

	int msgid;
	msgid = msgget(1234, 0); 

	if (msgid == -1)
	  ERR_EXIT("msgget");
	struct msgbuf *ptr;
	ptr = (struct msgbuf*)malloc(sizeof(long)+MSGMAX);
	ptr->mtype = type;
	int n = 0;
	if(( n = msgrcv(msgid, ptr, MSGMAX, type, flag))< 0)
	  ERR_EXIT("msgsnd");

	printf("read %d\n bytes, type = %d\n", n, (int)ptr->mtype);
	return 0;
}
