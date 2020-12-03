#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <signal.h>

int flag = 0;

static void parent_handler(int signo)
{
	if (signo == SIGUSR1)
	{
		flag = 1;
	}
}

static void child_handler(int signo, siginfo_t *info, void* extr)
{
	if (signo == SIGTERM)
	{
		exit(0);
	}
	else
	{
		printf("Signal : %s , From : %d , Value : %d\n",sys_siglist[signo],(int)info->si_pid, info->si_value.sival_int);
	}
}

int main(int argc, char const *argv[])
{
	int read;
	if (argc == 2)
	{
		read = atoi(argv[1]);
	}
	else
	{
		printf("%s\n", "Invalid args");
		exit(0);
	}

	int chpid;
	if ((chpid = fork()))
	{
		signal(SIGUSR1,parent_handler);
		int i = 0;
		while(flag == 0){}
		flag = 0;
		union sigval val;
		while(i < read)
		{
			val.sival_int = i;
			sigqueue(chpid,SIGUSR1,val);
			sleep(1);
			i++;
		}
		sigqueue(chpid,SIGTERM,(const union sigval)NULL);
		wait(NULL);
		exit(0);
	}
	else
	{
		struct sigaction act;
		sigfillset(&act.sa_mask);
		act.sa_flags = SA_SIGINFO;
		act.sa_sigaction = child_handler;
		sigaction(SIGTERM,&act,NULL);
		sigaction(SIGUSR1,&act,NULL);
		kill(getppid(),SIGUSR1);
		while(1){pause();}
	}

	return 0;
}