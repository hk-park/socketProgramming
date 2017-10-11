#include <stdio.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <string.h>
#include <unistd.h>
 
#define PORT 9000
#define BUFSIZE 100
#define SLEEPTIME 1
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
		while(1){
			memset(rcvBuffer, 0, BUFSIZE);
			if((readSize = read(c_socket, rcvBuffer, sizeof(rcvBuffer))) < 0) {
               	 		return -1;
        		}
			printf("Received Data From Client: %s\n", rcvBuffer);
			if(strcasecmp(rcvBuffer, "quit") == 0){
				break;
			}else if(strcasecmp(rcvBuffer, "hello") == 0){
				strcpy(buffer, "Hello, Nice to meet you");
			}else if(strcasecmp(rcvBuffer, "how are you?") == 0){
				strcpy(buffer, "Fine. Thank you. And you?");
			}else if(strcasecmp(rcvBuffer, "What's your name?") == 0){
				strcpy(buffer, "My name is hongkyu park.");
			}else if(strcasecmp(rcvBuffer, "Do you like sports?") == 0){
				strcpy(buffer, "Yes. I like soccer");
			}else{
				strcpy(buffer, "I don't understand what you say.");
			}
			n = strlen(buffer);
			sleep(SLEEPTIME);
			write(c_socket, buffer, n);
			printf("Send Data: %s\n", buffer);
			//write(c_socket, rcvBuffer, strlen(rcvBuffer));
			//printf("Send Data: %s\n", rcvBuffer);
		}
		close(c_socket);
	}	
	close(s_socket);
}
