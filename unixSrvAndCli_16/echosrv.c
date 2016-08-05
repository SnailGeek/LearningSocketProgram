#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/un.h>

#define ERR_EXIT(m)\
do\
{\
	perror(m);\
	exit(EXIT_FAILURE);\
}while(0)

void echo_srv(int conn)
{
	char recvbuf[1024];
	int n;
	while(1){
		memset(recvbuf, 0, sizeof(recvbuf));
		n = read(conn, recvbuf, sizeof(recvbuf));
		if( n == -1){
			if( n == EINTR)
			  continue;
			ERR_EXIT("read");
		}
		else if( n == 0){
			printf("client close\n");
			break;
		}
		fputs(recvbuf, stdout);
		write(conn, recvbuf, strlen(recvbuf));
	}
	close(conn);
}

int main(void)
{
	int listenfd;

	if((listenfd = socket(PF_UNIX, SOCK_STREAM, 0)) < 0)
	  ERR_EXIT("socket");

	unlink("/tmp/test_socket");//自动删除产生的套接口文件
	struct sockaddr_un servaddr;
	memset(&servaddr, 0, sizeof(servaddr));
	servaddr.sun_family = AF_UNIX;
	strcpy(servaddr.sun_path, "/tmp/test_socket");//绑定的时候会生成一个套接口文件

	if(bind(listenfd, (struct sockaddr*)&servaddr, sizeof(servaddr)) < 0)
	  ERR_EXIT("bind error");

	if(listen(listenfd, SOMAXCONN) < 0)
	  ERR_EXIT("listen");

	int conn;
	pid_t pid;
	while(1){
		conn = accept(listenfd, NULL, NULL);
		if(conn == -1){
			if(conn == EINTR)
			  continue;
			ERR_EXIT("accept");
		}

		pid = fork();
		if(pid == -1)
		  ERR_EXIT("fork");
		if(pid == 0){
			close(listenfd);
			echo_srv(conn);
			exit(EXIT_SUCCESS);
		}
		close(conn);
	}
	return 0;
}
