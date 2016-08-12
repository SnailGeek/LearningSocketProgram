#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <pthread.h>

#define ERR_EXIT(m)\
do\
{\
	perror(m);\
	exit(EXIT_FAILURE);\
}while(0)

void echo_srv(int conn)
{
	char recvbuf[1024];
	while(1){
		memset(recvbuf, 0, sizeof(recvbuf));
		int ret = read(conn, recvbuf, sizeof(recvbuf));
		if(ret == 0){
			printf("client_close\n");
			break;
		}
		else if(ret == -1)
		  ERR_EXIT("read");
		fputs(recvbuf, stdout);
		write(conn, recvbuf, ret);
	}
	return 0;
}

void thread_routine(void *arg)
{
	pthread_detach(pthread_self());
	int conn = (int)arg;
	echo_srv(conn);
	printf("exit thread...\n");
	return NULL;
}

int main(void)
{
	int listenfd;
	if((listenfd = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0)
		ERR_EXIT("socket");

	struct sockaddr_in servaddr;
	memset(&servaddr, 0, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(5188);
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);//表示本机的任意地址
	

	int on = 1;
	if(setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on))< 0)
		        ERR_EXIT("setxockopt");

    if(bind(listenfd, (struct sockaddr*)&servaddr, sizeof(servaddr))<0)
        ERR_EXIT("bind");
    if(listen(listenfd, SOMAXCONN) < 0)
        ERR_EXIT("listen");

    struct sockaddr_in peeraddr;
    socklen_t peerlen = sizeof(peeraddr); // 对方的地址长度一定要有初始值
    int conn;// 已连接套接字


	
	char recvbuf[1024];
    while(1){
		if((conn = accept(listenfd,(struct sockaddr*)&peeraddr,&peerlen))<0)
			ERR_EXIT("accept");
        memset(recvbuf, 0,sizeof(recvbuf));
		printf("ip=%s port=%d\n",inet_ntoa(peeraddr.sin_addr), ntohs(peeraddr.sin_port)) ;

		pthread_t tid;
		int ret;
		 
//		ret = pthread_create(&tid, NULL, thread_routine, (void *)&conn) // 这种做法是有问题，出现race condition(静态问题)
//		，因为一个主线程在创建一个新的新的线程之后就会继续监听，当有另一个套接字到来的时候，就会改变conn的值，
//		而如果新的线程还没有来得及将原来的conn取走那走那么这个时候就会出现问题。

		/*
		int *p =(int *)malloc(sizeof(int));
		*p = conn;
		pthread_create(&tid, NULL, thread_routine, p);
		*/ //这种用法会更好一些，没有不可移植的缺点

		if((ret = pthread_create(&tid, NULL, thread_routine, (void *)conn)) != 0){
			fprintf(stderr, "pthread_create:%s\n", strerror(ret));
			exit(EXIT_FAILURE);
		}


    }
    return 0;
}
