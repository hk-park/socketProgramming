#include <stdio.h>
#include <pthread.h>

int global = 10;

void *updateValue(void *data){
	global = global + 10;
	int local = *(int *)data;
	local++;
	printf("[CHILD] global = %d, local = %d\n", global, local);
}
int main(){
	int local = 0;
	int thread_id;
	pthread_t pthread;
	thread_id = pthread_create(&pthread, NULL, updateValue, (void *)&local);
	pthread_join(pthread, NULL);
	local = local + 100;
	global++;
	printf("[PARENT] global = %d, local = %d\n", global, local);		
	return 0;
}
