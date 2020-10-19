#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char const *argv[])
{
	int current_child = 0;
	int required = 0;

	if(argc == 2)
	{
		required = atoi(argv[1]);
	}

	/*if (required > sysconf(_SC_CHILD_MAX));
	{
		printf("%s\n", "Error");
		return 0;
	}
*/
	while(current_child < required)
	{
		pid_t pid = fork();
		if (pid == 0)
		{
			printf("%d in endles while\n", getpid());
			while(1){};
		}
		else if (pid > 0)
		{
			current_child+=1;
		}
		else
		{
			printf("%s\n", "Error");
		}
	}

	system("ps");
	int current_pid  = getpid();
	for (int i = 1; i <= required; ++i)
	{
		char buffer[10] = {};
		snprintf(buffer,10,"%d",current_pid+i);
		char command[256] = {};
		strcat(command,"kill ");
		strcat(command,buffer);
		system(command);
	}

	return 0;
}

