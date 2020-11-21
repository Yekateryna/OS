#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

struct Thread_data
{
	int* arr;
	int len;
	pthread_rwlock_t lock;
};

void read_func(void* arg)
{
	struct Thread_data* data = (struct Thread_data*)arg;	
	while(1)
	{
		int index = rand()%data->len;
		pthread_rwlock_rdlock(&(data->lock));
		printf("Thread %u read by index %d value = %d\n",pthread_self(),index,data->arr[index]);
		pthread_rwlock_unlock(&(data->lock));
		sleep(1+rand()%10);
	}
	return NULL;
}

void write_func(void* arg)
{
	struct Thread_data* data = (struct Thread_data*)arg;
	while(1)
	{
		pthread_rwlock_wrlock(&(data->lock));
		data->arr[rand()%data->len] = 1+rand()%100;
		pthread_rwlock_unlock(&(data->lock));
		sleep(1+rand()%10);
	}
	return NULL;
}

void det(void* arg)
{
	struct Thread_data* data = (struct Thread_data*)arg;
	while(1)
	{
		printf("\nDet: ");
		for (int i = 0; i < data->len; ++i)
		{
			printf("%d ", data->arr[i]);
		}
		printf("\n");
		sleep(5);
	}
}

void init_thread_data(struct Thread_data* data,int num)
{
	data->arr = (int*)malloc(num*sizeof(int));
	data->len = num;
	if (pthread_rwlock_init(&(data->lock),NULL))
	{
		printf("%s\n", "Error when init rwlock");
	}
}

void destroy_thread_data(struct Thread_data* data)
{
	free(data->arr);
	pthread_rwlock_destroy(&(data->lock));
}

int main(int argc, char const *argv[])
{
	setbuf(stdout,NULL);
	srand(time(NULL));
	int n = 10;
	if (argc==2)
	{
		n = atoi(argv[1]);
	}

	pthread_t* w = (pthread_t*)malloc(((int)n/2)*sizeof(pthread_t));
	pthread_t* r = (pthread_t*)malloc(n*sizeof(pthread_t));

	struct Thread_data data;
	init_thread_data(&data,n);

	pthread_t pid;
	pthread_attr_t attr;

	pthread_attr_init(&attr);
	pthread_attr_setdetachstate(&attr,PTHREAD_CREATE_DETACHED);
	pthread_create(&pid,&attr,&det,&data);

	
	for (int i = 0; i < n/2; ++i)
	{
		pthread_create(&w[i],NULL,&write_func,&data);
	}
	for (int i = 0; i < n; ++i)
	{
		pthread_create(&r[i],NULL,&read_func,&data);
	}
	for (int i = 0; i < n/2; ++i)
	{
		pthread_join(w[i],NULL);
	}
	for (int i = 0; i < n; ++i)
	{
		pthread_join(r[i],NULL);
	}
	
	destroy_thread_data(&data);
	free(w);
	free(r);
	return 0;
}