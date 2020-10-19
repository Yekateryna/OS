#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char const *argv[])
{
	int delay = 5;
	long iter = 0;

	if (argc == 2)
	{
		delay = atoi(argv[1]);
	}
	
	pid_t pid = fork();
	int start = time(NULL);
	while(time(NULL)-start <= 5)
	{
		iter+=1;
	}
	if (pid == 0)
	{
		printf("In child = %d\n", iter);
	}
	else
	{
		printf("In parent = %d\n", iter);	
	}
	return 0;
}