#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/unistd.h>
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
size_t recv_peek(int sockfd, void *buf, size_t len)//接受数据不从缓冲区中删除数据
{
	    while(1){
			int ret = recv(sockfd, buf, len, MSG_PEEK);
			if(ret == -1 && errno == EINTR)
				continue;
			return ret;
		}
}

size_t readline(int sockfd, void *buf, size_t maxline) //封装的readline函数只能用于套接口，因为用recv函数来实现的
{
	int ret;
	int nread;// 接受到的字节数
	char *bufp = buf;
	int nleft = maxline;
	while(1){
		ret = recv_peek(sockfd, bufp, nleft);//利用bufp去偷窥数据，直到遇到'\n'
		if(ret < 0)
		  return ret;
		else if(ret == 0)
		  return ret;
		nread = ret;
		int i;
		for(i = 0; i < nread; i++){
			if(bufp[i] == '\n'){
				ret = readn(sockfd, bufp, i+1);	
				if(ret != i+1)
					exit(EXIT_SUCCESS);
				return ret;
			}
		}
		if(nread > nleft){
			exit(EXIT_SUCCESS);
		}
		nleft -= nread;
		ret = readn(sockfd, bufp, nread);
		if(ret != nread)
			exit(EXIT_SUCCESS);
		bufp += nread;
	}
	return -1;
}

void echo_cli(int sock)
{
	char sendbuf[1024];
	char recvbuf[1024];
    while(fgets(sendbuf, sizeof(sendbuf), stdin) != NULL){

        writen(sock, sendbuf, strlen(sendbuf));

		int ret = readline(sock, recvbuf, sizeof(recvbuf));
		if(ret == -1)
			ERR_EXIT("read");
		else if(ret == 0)
		{
			printf("client close\n");
			break;
		}

        fputs(recvbuf, stdout);
        memset(sendbuf,0, sizeof(sendbuf));
        memset(recvbuf,0,sizeof(recvbuf));
	}
	close(sock);

}
int main()
{
	int sock[5];
	int i = 0;
	for(i = 0; i < 5; ++i){
		if((sock[i] = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0)
			ERR_EXIT("socket");

		struct sockaddr_in servaddr;
		memset(&servaddr, 0, sizeof(servaddr));	
		servaddr.sin_family = AF_INET;
		servaddr.sin_port = htons(5188);
		servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    
		if( connect(sock[i], (struct sockaddr*)&servaddr, sizeof(servaddr)) < 0)
			ERR_EXIT("connect");
    
		struct sockaddr_in localaddr;
		socklen_t addrlen = sizeof(localaddr);
		if(getsockname(sock[i], (struct sockaddr*)&localaddr,&addrlen) < 0)
		  ERR_EXIT("getsockname");
		printf("ip=%s port=%d\n",inet_ntoa(localaddr.sin_addr), ntohs(localaddr.sin_port)) ;
	}

	echo_cli(sock[0]);
    return 0;
}
