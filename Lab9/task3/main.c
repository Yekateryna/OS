#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <signal.h>

char* str = "parent";
int pid_addr;

static void signal_handler(int signo)
{
	if (signo == SIGUSR1)
	{
		printf("%s\n", str);
		sleep(1);
		kill(pid_addr,SIGUSR1);
	}
}

int main(int argc, char const *argv[])
{
	if (signal(SIGUSR1,signal_handler) == SIG_ERR)
	{
		fprintf(stderr, "%s\n", "Error SIGUSR1 init");
	}

	if (pid_addr=fork())
	{
		raise(SIGUSR1);
		while(1)
		{
			pause();
		}
	}
	else
	{
		pid_addr = getppid();
		str = "child";
		while(1)
		{
			pause();
		}
	}
	return 0;
}