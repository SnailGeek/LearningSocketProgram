#include <stdio.h>
#include <signal.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>

#define ERR_EXIT(m)\
do\
{\
	perror(m);\
	exit(EXIT_FAILURE);\
}while(0)
void handler(int sig)
{
	printf("recv a sig = %d\n", sig);
	exit(EXIT_SUCCESS);
}
int main(void)
{
	int listenfd;
	/*if((listenfd = socket(PF_INET, SOCK_STRAM, 0))<0);*/
	if((listenfd = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0)
		ERR_EXIT("socket");

	struct sockaddr_in servaddr;
	memset(&servaddr, 0, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(5188);
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);//表示本机的任意地址
//	servaddr.sin_addr.s_addr = htonol(INADDR_ANY);
//    servaddr.sin_addr.s_addr = inet_addr("127, 0, 0, 1");
//    inet_aton("127.0.0.1", &servaddr.sin_addr);
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
    if((conn = accept(listenfd,(struct sockaddr*)&peeraddr,&peerlen))<0)
        ERR_EXIT("accept");

    printf("ip=%s port=%d\n",inet_ntoa(peeraddr.sin_addr), ntohs(peeraddr.sin_port)) ;

	
	pid_t pid;
    pid = fork();
	if(pid == -1)
	  ERR_EXIT("fork");

	if(pid == 0)
	{
		signal(SIGUSR1, handler);
		char sendbuf[1024] = {0};
		while(fgets(sendbuf, sizeof(sendbuf), stdin)!= NULL){
			write(conn, sendbuf, strlen(sendbuf));
			memset(sendbuf, 0, sizeof(sendbuf));
		}
		printf("child close");
		exit(EXIT_SUCCESS);
	}
	else
	{
		char recvbuf[1024];
		while(1){
			memset(recvbuf, 0,sizeof(recvbuf));
			int ret = read(conn,  recvbuf, sizeof(recvbuf));
			if(ret == -1)
			  ERR_EXIT("read");
			else if(ret == 0)
			{
				printf("peer_close\n");
				break;
			}
	        fputs(recvbuf, stdout);
		}	
		printf("parent close");
		kill(pid, SIGUSR1);
		exit(EXIT_SUCCESS);
	}

    return 0;
}