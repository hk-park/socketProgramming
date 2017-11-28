#include <stdio.h>
#include <pthread.h>

void *func_pthread(void *);

int
main(int argc, char **argv){

	int sts;
	pthread_t thread_id;
	void *t_return;

	if((sts = pthread_create(&thread_id, NULL, func_pthread, NULL)) != 0 ) {
		perror("pthread create error\n");
		exit(1);
	}
	printf("thread %x is created\n", thread_id);
	sleep(3);
	printf("main function exit\n");
	return 0;
}

void *func_pthread(void *arg)
{
	int i;
	while(1) {
		sleep(1);
		printf("thread executing....\n");
	}

}
