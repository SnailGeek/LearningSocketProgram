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
#include <pthread.h>

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


void* thread_routine(void *arg)
{
	int i;
	for(i = 0; i < 20; i++){
		printf("B");
		fflush(stdout);
		usleep(20);
//		if( i== 3)
//		  pthread_exit("ABC");
	}
	return "DEF";
}

int main(void)
{
	pthread_attr_t attr;
	pthread_attr_init(&attr);

	int state;
	pthread_attr_getdetachstate(&attr, &state);
	if(state == PTHREAD_CREATE_JOINABLE)
	  printf("detachstate:PTHREAD_CREATE_JOINABLE]\n");
	else if(state == PTHREAD_CREATE_DETACHED)
	  printf("detachsate:PTHREAD_CREATE_DETACHED\n");

	size_t size;
	pthread_attr_getstacksize(&attr, &size);
	printf("stacksize:%d\n", (int)size);

	pthread_attr_getguardsize(&attr, &size);
	printf("guardesize:%d\n", (int)size);

	int scope;
	pthread_attr_getscope(&attr, &scope);
	if(scope == PTHREAD_SCOPE_PROCESS)
	  printf("scope:PTHREAD_SCOPE_PROCESS\n");
	else if(scope == PTHREAD_SCOPE_SYSTEM)
	  printf("scope:PTHREAD_SCOPE_SYSTEM\n");

	int policy;
	pthread_attr_getschedpolicy(&attr, &policy);
	if(policy == SCHED_FIFO)
	  printf("policy:SCHED_FIFO\n");
	else if(policy == SCHED_RR)
	  printf("policy:SCHED_RR\n");
	else if(policy == SCHED_OTHER)
	  printf("policy:SCHED_OTHER\n");

	int inheritsched;
	pthread_attr_getinheritsched(&attr, &inheritsched);
	if( inheritsched == PTHREAD_INHERIT_SCHED)
	  printf("inheritsched:PTHREAD_INHERIT_SCHED\n");
	else if(inheritsched == PTHREAD_EXPLICIT_SCHED)
	  printf("inheritsched:PTHREDA_EXPLICIT_SCHED\n");

	pthread_attr_destroy(&attr);
    return 0;
}
