#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

struct Targ
{
	char* name;
	char* str;
	int num;
};

void* child_thread(struct Targ* args)
{
	char* name = args->name;
	char* str = args->str;
	int num = args->num;

	for(int i = 0;i<num;i++)
	{
		printf("%s. %s : %d/%d\n",name,str,i+1,num);
	}
	return NULL;
}

int main(void)
{
	pthread_t tid;

	struct Targ arg_arr[] = {{"Name1","str1",1},{"Name2","str2",2},{"Name3","str3",3},{"Name4","str4",4}};

	setbuf(stdout,NULL);
	for (int i = 0; i < 4; ++i)
	{	
		if (pthread_create(&tid,NULL,child_thread,arg_arr+i))
		{
			printf(stderr, "%s\n", "Error!");
			return -1;
		}
	}
	sleep(2);
	return 0;
}