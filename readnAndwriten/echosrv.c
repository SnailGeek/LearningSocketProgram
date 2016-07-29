#include <stdio.h>
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

struct packet
{
	int len; // 包头存放着包体中实际的数据的长度
	char buf[1024]; // 包体
};

ssize_t readn(int fd, void *buf, size_t count)
{
	    size_t nleft = count; // 剩余的字节数
		ssize_t nread; //已接受的字节数
		char *bufp = (char*)buf;

		while(nleft > 0){
			if((nread = read(fd, bufp,nleft))< 0){
				if(errno == EINTR)
					continue;
				return -1;
			}
			else if(nread == 0)// nread为零意味着对等方关闭了，read函数返回零
				return count - nleft;
			bufp += nread;
			nleft -= nread;
		}
		return count;
}

ssize_t writen(int fd, const void *buf, size_t count)
{
	    size_t nleft = count; // 剩余的字节数
		ssize_t nwritten; //已接受的字节数
		char *bufp = (char*)buf;
		while(nleft > 0){
			if((nwritten = write(fd, bufp,nleft))< 0){ //write返回小于零的数，信号中断
				if(errno == EINTR)
					continue;
				return -1;
			}
			else if(nwritten == 0)// nread为零意味着对等方关闭了，read函数返回零
				continue;
			bufp += nwritten;
			nleft -= nwritten;
		}
		return count;
}



void do_service(int conn)
{
	struct packet recvbuf;
	int n;
	while(1){
		memset(&recvbuf, 0,sizeof(recvbuf));
		int ret = readn(conn,  &recvbuf.len, 4);
		if(ret == -1)
			ERR_EXIT("read");
		else if(ret < 4)
		{
			printf("client_close\n");
			break;
		}
		n = ntohl(recvbuf.len);
		ret = readn(conn, recvbuf.buf, n);
		if(ret == -1)
			ERR_EXIT("read");
		else if(ret < n)
		{
			printf("client_close\n");
			break;
		}
		fputs(recvbuf.buf, stdout);
		writen(conn, &recvbuf, 4+n);
	}
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
//
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
	pid_t pid;

	while(1)
	{
		if((conn = accept(listenfd,(struct sockaddr*)&peeraddr,&peerlen))<0)
			ERR_EXIT("accept");

	    printf("ip=%s port=%d\n",inet_ntoa(peeraddr.sin_addr), ntohs(peeraddr.sin_port)) ;

		pid = fork();
		if(pid == -1)
		  ERR_EXIT("fork");
		if(pid == 0)
		{
			close(listenfd);
			do_service(conn);
			exit(EXIT_SUCCESS);


		}
		else close(conn);

	}
    return 0;
}
