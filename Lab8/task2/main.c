#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

struct Thread_data
{
	pthread_cond_t cond;
	pthread_mutex_t mutex;
	int data;
};

void Thread_data_init(struct Thread_data* data)
{
	if (pthread_cond_init(&(data->cond),NULL))
	{
		printf("%s\n", "error when cond init");
	}
	pthread_mutex_init(&(data->mutex),NULL);
	data->data = 0;
}

void Thread_data_destroy(struct Thread_data* data)
{
	pthread_cond_destroy(&(data->cond));
	pthread_mutex_destroy(&(data->mutex));
}

void producer(void* arg)
{
	struct Thread_data* data = (struct Thread_data*)arg;
	while(1)
	{
		int r = 1+rand()%100;
		pthread_mutex_lock(&(data->mutex));
		data->data = r;
		pthread_cond_signal(&(data->cond));
		pthread_mutex_unlock(&(data->mutex));
		sleep(5);
	}
}

void consumer(void* arg)
{
	struct Thread_data* data = (struct Thread_data*)arg;
	while(1)
	{
		int read;
		pthread_mutex_lock(&(data->mutex));
		pthread_cond_wait(&(data->cond),&(data->mutex));
		read = data->data;
		pthread_mutex_unlock(&(data->mutex));
		printf("%d\n", read);
		sleep(5);
	}
}

int main(int argc, char const *argv[])
{
	setbuf(stdout,NULL);
	srand(time(NULL));
	struct Thread_data data;
	Thread_data_init(&data);
	pthread_t pid1;
	pthread_t pid2;
	pthread_create(&pid1,NULL,&producer,&data);
	pthread_create(&pid2,NULL,&consumer,&data);
	pthread_join(pid1,NULL);
	pthread_join(pid2,NULL);
	Thread_data_destroy(&data);
	return 0;
}