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

int main()
{
	int sock;
	if((sock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0)
		ERR_EXIT("socket");

	struct sockaddr_in servaddr;
	memset(&servaddr, 0, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(5188);
    servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    
    if( connect(sock, (struct sockaddr*)&servaddr, sizeof(servaddr)) < 0)
        ERR_EXIT("connect");
    
	struct packet sendbuf;
	struct packet recvbuf;
	memset(&sendbuf, 0, sizeof(sendbuf));
	memset(&recvbuf, 0, sizeof(recvbuf));
	int n;


    while(fgets(sendbuf.buf, sizeof(sendbuf.buf), stdin) != NULL){

		n = strlen(sendbuf.buf);
		sendbuf.len = htonl(n);
        writen(sock, &sendbuf, 4+n);

		int ret = readn(sock, &recvbuf.len, 4);
		if(ret == -1)
			ERR_EXIT("read");
		else if(ret < 4)
		{
			printf("client close\n");
			break;
		}

		n = ntohl(recvbuf.len);
		ret = readn(sock, recvbuf.buf, n);
		if(ret == -1)
			ERR_EXIT("read");
		else if(ret < n)
		{
			printf("client close\n");
			break;
		}

        fputs(recvbuf.buf, stdout);
        memset(&sendbuf,0, sizeof(sendbuf));
        memset(&recvbuf,0,sizeof(recvbuf));
    }
    close(sock);

    return 0;
}
