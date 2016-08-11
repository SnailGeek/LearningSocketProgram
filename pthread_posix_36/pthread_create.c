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
	pthread_t tid;
	int ret;

	if((ret = pthread_create(&tid, NULL, thread_routine, NULL)) != 0){
		fprintf(stderr, "pthread_create:%s\n", strerror(ret));
		exit(EXIT_FAILURE);
	}

	int i;
	for(i = 0; i < 20; i++){
		printf("A");
		fflush(stdout);
		usleep(20);
	}
	void* value;
	if((ret = pthread_join(tid, &value)) != 0){
		fprintf(stderr, "pthread_join:%s\n", strerror(ret));
		exit(EXIT_FAILURE);

	}
	printf("\n");
	printf("return message%s\n", (char*)value);

    return 0;
}
