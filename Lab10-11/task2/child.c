#include <stdio.h>
#include <stdlib.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <sys/sem.h>
#include <unistd.h>
#include <signal.h>

int flag = 0;
int* shm_buf;
int shm_id = -1;
int n = 0;
int sem_id = -1;
struct sembuf sb[1];


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
		else if (sem_id == -1)
		{
			sem_id = info->si_value.sival_int;
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

	kill(getppid(),SIGUSR1);

	while(flag == 0){pause();}
	flag=0;

	while(1){
		sb[0].sem_num = 0;
		sb[0].sem_op = -1;
		semop(sem_id,sb,1);

		int i = semctl(sem_id,0,GETVAL,NULL);
		if (i != 0)
		{
			shm_buf[0]+=shm_buf[i];
		}
		//kill(getppid(),SIGUSR1);
	}

	return 0;
}