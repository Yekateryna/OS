#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

void clean_buf(void* buffer)
{
	free(buffer);
	printf("%s\n", "buffer cleaned");
}

void thread()
{
	void* mem = malloc(1024);
	
	pthread_cleanup_push(clean_buf,mem);
	
	int i = 0;
	while(1)
	{
		printf("Iteration # %d\n", i);
		i++;
		sleep(1);
	}
	pthread_cleanup_pop(1);
}

int main(int argc, char const *argv[])
{
	setbuf(stdout,NULL);
	void* result;
	int num;
	pthread_t tid;
	if (argc != 2)
	{
		printf("%s\n","Error");
		return EXIT_FAILURE;
	}
	else
	{
		num = atoi(argv[1]);
	}
	
	if (pthread_create(&tid,NULL,&thread,NULL)!=0)
	{
		printf("%s\n", "Error Can't create thread");
		return EXIT_FAILURE;
	}

	sleep(num);
	pthread_cancel(tid);
	if (!pthread_equal(pthread_self(),tid))
	{
		pthread_join(tid,&result);
	}
	if (result == PTHREAD_CANCELED)
	{
		printf("%s\n", "Thread was canceled");
	}
	return 0;
}