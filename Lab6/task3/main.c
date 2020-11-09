#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

void* thread_func(void* arg)
{
	pthread_setcancelstate(PTHREAD_CANCEL_DISABLE,NULL);
	int num = *(int*)arg;
	for (int i = 0; i < num; ++i)
	{
		printf("Iter # %d\n", i);
		sleep(1);
	}
	return NULL;
}

int main(int argc, char const *argv[])
{
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
		num*=2;
	}

	if (pthread_create(&tid,NULL,&thread_func,&num)!=0)
	{
		printf("%s\n","Error when called _create");
		return EXIT_FAILURE;	
	}

	sleep(num/2);

	void* result;
	printf("%s\n", "Canceling thread");
	pthread_cancel(tid);
	if (!pthread_equal(pthread_self(),tid))
	{
		pthread_join(tid,&result);
	}

	if (result == PTHREAD_CANCELED)
	{
		printf("%s\n", "Thread was canceled");
	}
	else
	{
		printf("%s\n", "Thread finished normally");
	}
	return 0;
}