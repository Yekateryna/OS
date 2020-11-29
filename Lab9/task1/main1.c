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

	struct sigaction arg = {signal_handler,NULL,NULL,NULL,NULL};
	struct sigaction arg_DFL = {SIG_DFL,NULL,NULL,NULL,NULL};
	struct sigaction arg_IGN = {SIG_IGN,NULL,NULL,NULL,NULL};

	if (sigaction(SIGINT,&arg,NULL) == SIG_ERR)
	{
		fprintf(stderr, "%s\n", "Error SIGINT init");
	}
	if (sigaction(SIGTERM,&arg,NULL) == SIG_ERR)
	{
		fprintf(stderr, "%s\n", "Error SIGTERM init");
	}
	if (sigaction(SIGUSR1,&arg,NULL) == SIG_ERR)
	{
		fprintf(stderr, "%s\n", "Error SIGUSR1 init");
	}
	if (sigaction(SIGPROF,&arg_DFL,NULL) == SIG_ERR)
	{
		fprintf(stderr, "%s\n", "Error SIGPROF init");
	}
	if (sigaction(SIGHUP,&arg_IGN,NULL) == SIG_ERR)
	{
		fprintf(stderr, "%s\n", "Error SIGHUP init");
	}

	while(1)
		pause();
	return 0;
}