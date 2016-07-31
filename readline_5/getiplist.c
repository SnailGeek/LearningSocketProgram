#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <netdb.h>

#define ERR_EXIT(m)\
do\
{\
	perror(m);\
	exit(EXIT_FAILURE);\
}while(0)

int getlocal(char *ip)
{
	 char host[100] = {0};
	if(gethostname(host, sizeof(host)) < 0)
	  ERR_EXIT("gethostname");
	struct hostent* hp;
	hp = gethostbyname(host);
	if(hp == NULL)
	  return -1;

	strcpy(ip,inet_ntoa(*(struct in_addr*)hp->h_addr));
	return 0;
}

int main(void)
{
	char host[100] = {0};
	if(gethostname(host, sizeof(host)) < 0)
	  ERR_EXIT("gethostname");
	struct hostent* hp;
	hp = gethostbyname(host);
	if(hp == NULL)
	  ERR_EXIT("gethostbyname");
	
	int i = 0;
	while(hp->h_addr_list[i] != NULL){
		printf("%s\n", inet_ntoa(*(struct in_addr*)hp->h_addr_list[i]));
		i++;
	}
	char ip[16] = {0};
	getlocal(ip);
	printf("localip=%s\n", ip);
	return 0;

}
