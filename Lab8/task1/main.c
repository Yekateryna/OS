#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

int* arr;
sem_t lock;
sem_t empty_items;
sem_t full_items;

void producer()
{
	while(1)
	{
		int r = 1+rand()%100;
		int index;
		sem_wait(&empty_items);
		sem_getvalue(&empty_items,&index);
		sem_wait(&lock);
		arr[index] = r;
		sem_post(&lock);
		sem_post(&full_items);
		sleep(1);
	}
}

void consumer()
{
	while(1)
	{
		int get;
		int index;
		sem_getvalue(&empty_items,&index);
		sem_wait(&full_items);
		sem_wait(&lock);
		get = arr[index];
		sem_post(&lock);
		sem_post(&empty_items);
		printf("Get %d\n",get);
		sleep(1);
	}
}

int main(int argc, char const *argv[])
{
	setbuf(stdout,NULL);
	srand(time(NULL));
	int size = 10;
	if (argc==2)
	{
		size = atoi(argv[1]);
	}

	sem_init(&lock,0,1);
	sem_init(&empty_items,0,size);
	sem_init(&full_items,0,0);
	arr = (int*)malloc(size*sizeof(int));

	pthread_t pid1;
	pthread_t pid2;
	
	pthread_create(&pid1,NULL,&producer,NULL);
	pthread_create(&pid2,NULL,&consumer,NULL);

	pthread_join(pid1,NULL);
	pthread_join(pid2,NULL);
	free(arr);
	return 0;
}