#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

static pthread_key_t key;

void thread_func()
{
	int count = 1+rand()%10;
	char* str = (char*)pthread_getspecific(key);

	if (str == NULL)
	{
		char tmp[50];
		sprintf(tmp,"Thread #%d rand = ",pthread_self());
		pthread_setspecific(key,tmp);
		str = (char*)pthread_getspecific(key);		
	}

	for (int i = 0; i < count; ++i)
	{
		printf("%s%d\n",str,1+rand()%10);
		sleep(1);
	}
}

int main(int argc, char const *argv[])
{
	setbuf(stdout,NULL);
	int num;
	if (argc != 2)
	{
		printf("%s\n","Error");
		return EXIT_FAILURE;
	}
	else
	{
		num = atoi(argv[1]);
	}
	pthread_key_create(&key,NULL);

	pthread_t id[num];
	for (int i = 0; i < num; ++i)
	{
		pthread_create(&id[i],NULL,&thread_func,NULL);
	}
	for (int i = 0; i < num; ++i)
	{
		pthread_join(id[i],NULL);
	}

	return 0;
}