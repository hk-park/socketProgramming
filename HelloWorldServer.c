#include <stdio.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <string.h>
#include <unistd.h>
#include <dirent.h> 
#include <stdlib.h> 
 
#define PORT 9000
#define BUFSIZE 10000
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
	char *token;
	char tempBuf[BUFSIZE];
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
			}else if(strncasecmp(rcvBuffer, "strlen", 6) == 0){
				token = strtok(rcvBuffer, " "); //token = strlen
				token = strtok(NULL, " "); //token = 길이를 구하고자 하는 문자열
				strcpy(tempBuf, token);
				sprintf(buffer, "%s 문자열의 길이는 %d입니다.", tempBuf, strlen(tempBuf)); 				
			}else if(strncasecmp(rcvBuffer, "strcmp", 6) == 0){
				char str[3][BUFSIZE];
				int i = 0;
				token = strtok(rcvBuffer, " "); //token = strcmp
				while(token != NULL){
					strcpy(str[i], token);
					i++;
					token = strtok(NULL, " ");
				}
				if(strcasecmp(str[1], str[2])==0){
					sprintf(buffer, "%s와 %s는 같은 문자열입니다.", str[1], str[2]);
				}else{
					sprintf(buffer, "%s와 %s는 다른 문자열입니다.", str[1], str[2]);
				}
			}else if(strncasecmp(rcvBuffer, "readfile", 8) == 0){
				token = strtok(rcvBuffer, " ");
				token = strtok(NULL, " "); 
				FILE *fp = fopen(token, "r");
				char tempStr[BUFSIZE];
				memset(buffer, 0, BUFSIZE);
				while(fgets(tempStr, BUFSIZE, (FILE *)fp)){
					strcat(buffer, tempStr);
				}
				fclose(fp);
			}else if(strcasecmp(rcvBuffer, "ls")==0){
				DIR *dp;
				struct dirent *dir;
				int idx = 0;
				if((dp=opendir(".")) == NULL){
					printf("Directory open error\n");
					return -1;
				}
				memset(buffer, 0, BUFSIZE);
				while((dir = readdir(dp)) != NULL){
					if(dir->d_ino == 0) continue;
					sprintf(buffer, "%s\n[%d - %s]", buffer, idx++, dir->d_name);
					//strcat(buffer, dir->d_name);
				}
				closedir(dp);
			}else if(strncasecmp(rcvBuffer,"exec", 4)==0){
				char *command;
				token = strtok(rcvBuffer, " ");
				command= strtok(NULL, "\0");
				printf("command : %s\n", command);
				int result = system(command);
				printf("result: %d\n", result);
				if(result){
					sprintf(buffer, "[%s] command failed", command);
				}else{
					sprintf(buffer, "[%s] command is executed", command);
				}
				 
			} else{
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
