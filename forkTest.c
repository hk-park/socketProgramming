#include <stdio.h>

int global = 10;

int main(){
	int local = 0;
	int pid = fork();
	if(pid > 0){ //parent process
		local++;
		global++;
		printf("[PARENT] global = %d, local = %d\n", global, local);	
	}else if (pid == 0){ //child process
		local = local++;
		global = global + 10;
		printf("[CHILD] global = %d, local = %d\n", global, local);
	}else{
		printf("fork() is failed\n");
		return -1;
	}
	
	return 0;
}
