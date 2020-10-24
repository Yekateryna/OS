#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

struct Targ2
{
	int num;
	int min;
	int max;
	int for_exit;
};

struct Targ1
{
	int num;
	char* str;
};

void* child_1(struct Targ1* args)
{
	int num = args->num;
	char* str = args->str;

	for (int i = 0; i < num; ++i)
	{
		printf("%s : %d/%d\n",str,i,num);
	}
	return NULL;
}

void* child_2(struct Targ2* args)
{
	int num = args->num;
	int min = args->min;
	int max = args->max;
	int for_exit = args->for_exit;

	int current;
	for (int i = 0; i < num; ++i)
	{
		current = min+rand()%max;
		printf("%d: %d\n",i,current );
		if (current == for_exit)
		{
			printf("%s\n", "Generate for exit");
			return NULL;
		}
	}
	return NULL;
}

int main(void)
{
	setbuf(stdout,NULL);
	pthread_t tid1;
	pthread_t tid2;

	struct Targ1 args1 = {10, "Str 1"};

	struct Targ2 args2 = {10,0,50,40};

	if (pthread_create(&tid1,NULL,child_1,&args1))
	{
		printf(stderr, "%s\n", "Error!");
		exit(EXIT_FAILURE);
	}

	if (pthread_create(&tid2,NULL,child_2,&args2))
	{
		printf(stderr, "%s\n", "Error!");
		exit(EXIT_FAILURE);
	}

	pthread_join(tid1,NULL);
	pthread_join(tid2,NULL);
	printf("%s\n","Main thread finished");
	return 0;
}