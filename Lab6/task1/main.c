#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

struct Array
{
	int* arr;
	int size;
};

struct Arg
{
	int* arr;
	int num;
};

void* simple_thread(struct Arg* a)
{
	struct Arg arg = *(struct Arg*)a;
	arg.arr[arg.num] = 1+rand()%10;
	sleep(arg.arr[arg.num]);
}

void* det(void* arg)
{
	struct Array arr = *(struct Array*)arg;
	int flag = 0;
	while(flag == 0)
	{
		flag=1;
		for (int i = 0; i < arr.size; ++i)
		{
			printf("%d ", arr.arr[i]);
			flag*=arr.arr[i];
		}
		sleep(1);
		printf("\n");
	}
	return NULL;
}

int main(int argc, char const *argv[])
{
	setbuf(stdout,NULL);
	struct Array res;
	if (argc != 2)
	{
		printf("%s\n","Error");
	}
	else
	{
		res.size = atoi(argv[1]);
	}

	res.arr = (int*)calloc(res.size,sizeof(int));
	pthread_t* id = (pthread_t*)malloc(res.size*sizeof(pthread_t));
	struct Arg a;
	a.arr = res.arr;

	pthread_attr_t attr;
	pthread_t tid;

	pthread_attr_init(&attr);
	pthread_attr_setdetachstate(&attr,PTHREAD_CREATE_DETACHED);
	pthread_create(&tid,&attr,&det,&res);
	pthread_attr_destroy(&attr);

	for (int i = 0; i < res.size; ++i)
	{
		a.num = i;
		pthread_create(&id[i],NULL,&simple_thread,&a);
		pthread_join(id[i],NULL);
	}
	free(id);
	free(res.arr);
	return 0;
}