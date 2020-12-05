#include <stdio.h>
#include <stdlib.h>
#include <sys/shm.h>
#include <unistd.h>
#include <signal.h>

int flag = 0;
int* shm_buf;
int shm_id = -1;
int n = 0;

static void handler(int signo, siginfo_t *info, void* extr)
{
	if (signo == SIGINT)
	{
		shmdt(shm_buf);
		exit(0);
	}
	else if (signo == SIGUSR1)
	{
		if (shm_id == -1)
		{
			shm_id = info->si_value.sival_int;
			//printf("Child shm_id = %d\n", shm_id);		
		}
		else
		{
			n = info->si_value.sival_int;
		}
		flag = 1;
	}
}

int main(void)
{
	struct sigaction act;
	sigfillset(&act.sa_mask);
	act.sa_flags = SA_SIGINFO;
	act.sa_sigaction = handler;
	sigaction(SIGINT,&act,NULL);
	sigaction(SIGUSR1,&act,NULL);

	kill(getppid(),SIGUSR1);

	while(flag == 0){pause();}
	flag=0;

	shm_buf = (int*) shmat(shm_id,NULL,0);

	while(1){
		while(flag == 0){pause();}
		flag=0;
		for (int i = 1; i < n; ++i)
		{
			shm_buf[0]+=shm_buf[i];
		}
		kill(getppid(),SIGUSR1);
	}

	return 0;
}