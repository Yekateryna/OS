#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

pthread_t tid;

void* child_thread(void* arg)
{
	for (int i = 0; i < 10; ++i)
	{
		printf("Child Thread. Iteration : %d \n", i);
	}
	sleep(2);
	return NULL;
}

int main(void)
{
	setbuf(stdout,NULL);
	if (pthread_create(&tid,NULL,child_thread,NULL))
	{
		fprintf(stderr, "%s\n", "Error!");
		return -1;
	}
	for (int i = 0; i < 10; ++i)
	{
		printf("Main Thread. Iteration : %d\n", i);
	}
	sleep(2);
	return 0;
}