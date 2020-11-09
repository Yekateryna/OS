#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

double thread_func()
{
	pthread_setcanceltype(PTHREAD_CANCEL_DEFERRED,NULL);
	int old_cancel_state;
	double pi = 1;
	double p = 3;
	for (int i = 0; i < 100000; i+=1)
	{
		pthread_setcancelstate(PTHREAD_CANCEL_DISABLE,&old_cancel_state);
		if (i%2 == 0)
		{
			pi-=1/p;
		}
		else
		{
			pi+=1/p;
		}
		p+=2;
		pthread_setcancelstate(old_cancel_state,NULL);
		pthread_testcancel();
		printf("pi = %f\n",4*pi);
		sleep(1);
	}
	return pi;
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
	}

	if (pthread_create(&tid,NULL,&thread_func,NULL)!=0)
	{
		printf("%s\n","Error when called _create");
		return EXIT_FAILURE;	
	}

	sleep(num);

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
		printf("%s%f\n", "final pi = ",*(double*)result);
	}
	return 0;
}