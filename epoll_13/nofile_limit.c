#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <signal.h>
#include <sys/wait.h>
#include <sys/resource.h>
#include <sys/time.h>
#define ERR_EXIT(m)\
do\
{\
	perror(m);\
	exit(EXIT_FAILURE);\
}while(0)

int main(void)
{
	struct rlimit rl;
	if(getrlimit(RLIMIT_NOFILE, &rl)< 0)
	  ERR_EXIT("getrlimit");
	printf("%d\n", (int)rl.rlim_max);
	rl.rlim_cur = 2048;
	rl.rlim_max = 2048;
	if(setrlimit(RLIMIT_NOFILE, &rl)< 0)
	  ERR_EXIT("setrlimit");
	printf("%d\n", (int)rl.rlim_max);
	return 0;
}
