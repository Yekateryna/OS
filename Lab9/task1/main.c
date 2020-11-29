#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <signal.h>

static void signal_handler(int signo)
{
	if (signo == SIGINT)
	{
		printf("%s\n", "SIGINT");
	}
	else if (signo == SIGTERM)
	{
		printf("%s\n","SIGTERM");
	}
	else if (signo == SIGUSR1)
	{
		exit(0);
	}
}

int main(int argc, char const *argv[])
{
	setbuf(stdout,NULL);
	printf("%d\n",getpid());
	if (signal(SIGINT,signal_handler) == SIG_ERR)
	{
		fprintf(stderr, "%s\n", "Error SIGINT init");
	}
	if (signal(SIGTERM,signal_handler) == SIG_ERR)
	{
		fprintf(stderr, "%s\n", "Error SIGTERM init");
	}
	if (signal(SIGUSR1,signal_handler) == SIG_ERR)
	{
		fprintf(stderr, "%s\n", "Error SIGUSR1 init");
	}
	if (signal(SIGPROF,SIG_DFL) == SIG_ERR)
	{
		fprintf(stderr, "%s\n", "Error SIGPROF init");
	}
	if (signal(SIGHUP,SIG_IGN) == SIG_ERR)
	{
		fprintf(stderr, "%s\n", "Error SIGHUP init");
	}

	while(1)
		pause();
	return 0;
}