#include <stdio.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <string.h>
#include <unistd.h> //sleep() 함수를 사용하기 위한 헤더 파일
#define PORT 9000
#define IPADDR "127.0.0.1"
#define BUFSIZE 100
#define SLEEPTIME 10 //단계별로 10초 쉬었다가 다음 단계로 이동하도록 설정
main( )
{
	int	c_socket;
	struct sockaddr_in c_addr;
	int	len;
	int	n;
	
	char	rcvBuffer[BUFSIZE];
	char sendBuffer[BUFSIZE];
	c_socket = socket(PF_INET, SOCK_STREAM, 0);
	
	memset(&c_addr, 0, sizeof(c_addr));
	c_addr.sin_addr.s_addr = inet_addr(IPADDR);
	c_addr.sin_family = AF_INET;
	c_addr.sin_port = htons(PORT);
	
	if(connect(c_socket, (struct sockaddr *) &c_addr, sizeof(c_addr))==-1) {
		printf("Can not connect\n");
		close(c_socket);
		return -1;
	}
	printf("Connected!!\n");
	sleep(SLEEPTIME);
	printf("Input your message\n");
	//scanf("%s", sendBuffer);  //scanf는 공백 문자가 포함된 문자열을 인식하지 못하므로, scanf보다는 fgetsfmf 사용을 추천한다.
	fgets(sendBuffer, BUFSIZE, stdin);
	sendBuffer[strlen(sendBuffer)-1] = '\0';
	write(c_socket, sendBuffer, strlen(sendBuffer));
	printf("<%s> is sent.\n", sendBuffer);
	if((n = read(c_socket, rcvBuffer, sizeof(rcvBuffer))) < 0) {
		return (-1);
	}
	
	rcvBuffer[n] = '\0';
	printf("received Data : %s\n", rcvBuffer);
	printf("received Data Size: %d\n", strlen(rcvBuffer));	
	close(c_socket);
}

