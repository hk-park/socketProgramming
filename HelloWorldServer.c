#include <stdio.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <string.h>
#include <unistd.h>
 
#define PORT 9000
#define BUFSIZE 100
#define SLEEPTIME 10
char buffer[BUFSIZE] = "hello, I'm server";
char rcvBuffer[BUFSIZE];
main( )
{
	int   c_socket, s_socket;
	struct sockaddr_in s_addr, c_addr;
	int   len;
	int   n;
	int readSize;
 	s_socket = socket(PF_INET, SOCK_STREAM, 0);
	
	memset(&s_addr, 0, sizeof(s_addr));
	s_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	s_addr.sin_family = AF_INET;
	s_addr.sin_port = htons(PORT);
 
	if(bind(s_socket, (struct sockaddr *) &s_addr, sizeof(s_addr)) == -1) {
		printf("Can not Bind\n");
		return -1;
	}
 
	if(listen(s_socket, 5) == -1) {
		printf("listen Fail\n");
		return -1;
	}
 	
	while(1) {
		len = sizeof(c_addr);
		c_socket = accept(s_socket, (struct sockaddr *) &c_addr, &len);
		printf("Client is Connected\n");
		if((readSize = read(c_socket, rcvBuffer, sizeof(rcvBuffer))) < 0) {
               	 return -1;
        	}
		printf("Received Data From Client: %s\n", rcvBuffer);
		n = strlen(buffer);
		sleep(SLEEPTIME);
		write(c_socket, buffer, n);
		printf("Send Data: %s\n", buffer);
		close(c_socket);
	}	
	close(s_socket);
}
