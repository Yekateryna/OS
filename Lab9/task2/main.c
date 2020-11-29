#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <signal.h>

char* inp_str;

static void signal_handler(int signo)
{
	if (signo == SIGALRM)
	{
		printf("%s\n", inp_str);
		exit(0);
	}
}

int main(int argc, char const *argv[])
{
	setbuf(stdout,NULL);
	if (signal(SIGALRM,signal_handler) == SIG_ERR)
	{
		fprintf(stderr, "%s\n", "Error SIGALRM init");
	}
	int delay = 0;
	if (argc==3)
	{
		delay = atoi(argv[1]);
		inp_str = argv[2];
	}

	if (fork())
	{
		exit(0);
	}
	else
	{
		alarm(delay);
		while(1)
		{
			pause();
		}
	}

	return 0;
}