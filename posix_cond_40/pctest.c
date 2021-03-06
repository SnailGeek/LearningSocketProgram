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
#include <semaphore.h>
#define ERR_EXIT(m)\
do\
{\
	perror(m);\
	exit(EXIT_FAILURE);\
}while(0)


#define CONSUMERS_COUNT 2
#define PRODUCERS_COUNT 4


pthread_mutex_t g_mutex;
pthread_cond_t g_cond;

pthread_t g_thread[CONSUMERS_COUNT + PRODUCERS_COUNT];

int nready = 0; // 表示当前缓冲区中的产品个数
void* consume(void *arg)
{
	int num = (int)arg;
	while(1){
		pthread_mutex_lock(&g_mutex);
		while(nready == 0){
			printf("%d begin wait a condition..\n", num);
			pthread_cond_wait(&g_cond, &g_mutex);
		}
		printf("%d end wait a condition.. \n", num);
		printf("%d begin consume product \n", num);
		--nready;
		printf("%d end  consume product \n", num);
		pthread_mutex_unlock(&g_mutex);
		sleep(1);
	}
	return NULL;
}
void* produce(void *arg)
{
	int num = (int)arg;
	while(1){
		pthread_mutex_lock(&g_mutex);
		printf("%d  begin produce product \n", num);
		++nready;
		printf("%d  end  produce product \n", num);
		printf("%d signal.... \n", num);
		pthread_cond_signal(&g_cond);
		pthread_mutex_unlock(&g_mutex);
		sleep(1);

	}
	return NULL;
}
int main(void)
{	
	int i;

	pthread_mutex_init(&g_mutex, NULL);
	pthread_cond_init(&g_cond, NULL);


	for(i = 0; i < CONSUMERS_COUNT; i++)
		pthread_create(&g_thread[i], NULL, consume, (void*)i);
	sleep(1);
	for(i = 0; i < PRODUCERS_COUNT; i++)
		pthread_create(&g_thread[CONSUMERS_COUNT + i], NULL, produce, (void*)i);

	for(i = 0; i < CONSUMERS_COUNT + PRODUCERS_COUNT; i++)
	  pthread_join(g_thread[i], NULL);

	pthread_mutex_destroy(&g_mutex);
	pthread_cond_destroy(&g_cond);

    return 0;
}
