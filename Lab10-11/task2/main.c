#include <stdio.h>
#include <stdlib.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <sys/sem.h>
#include <unistd.h>
#include <signal.h>
#include <errno.h>

int flag = 0;
int chid;
int* shm_buf;
int shm_id;
int sem_id;
struct sembuf sb[1];

union semnum {
	int val;
	struct semid_ds* buf;
	unsigned short* array;
}sem_arg;

static void handler(int signo)
{
	if (signo == SIGINT)
	{
		sigqueue(chid,SIGINT,(const union sigval)NULL);
		int code;
		wait(&code);
		printf("Child exit with code %d\n", code);
		shmdt(shm_buf);
		shmctl(shm_id,IPC_RMID,NULL);
		semctl(sem_id,IPC_RMID,NULL);
		exit(0);

	}
	else if (signo == SIGUSR1)
	{
		flag = 1;
	}
}

void error_exit()
{
	printf("%s\n", "Error exit handler started");
	printf("Error code : %d\n", errno);
	raise(SIGINT);
}

int main(int argc, char const *argv[])
{
	if (argc != 2)
	{
		fprintf(stderr,"%s\n", "Invalid argv");
		exit(0);
	}
	int buf_size = atoi(argv[1]);
	if ((chid = fork()))
	{
		//main
		
		if (signal(SIGUSR1,handler)==SIG_ERR)
		{
			fprintf(stderr, "%s\n", "signal error");
			error_exit();
		}
		if (signal(SIGINT,handler)==SIG_ERR)
		{
			fprintf(stderr, "%s\n", "signal error");
			error_exit();
		}

		shm_id = shmget(IPC_PRIVATE,buf_size,IPC_CREAT|IPC_EXCL|0600);
		if (shm_id == -1)
		{
			fprintf(stderr,"%s\n", "shmget error");
			error_exit();
		}
		shm_buf = (int*) shmat(shm_id,NULL,0);
		if (shm_buf == (int*) -1)
		{
			fprintf(stderr, "%s\n", "shmat error");
			error_exit();
		}
		struct shmid_ds ds;
		shmctl(shm_id,IPC_STAT,&ds);
		if (ds.shm_segsz != buf_size)
		{
			fprintf(stderr, "%s\n", "size error");
			error_exit();
		}

		sem_id = semget(IPC_PRIVATE,1,0600|IPC_CREAT|IPC_EXCL);
		if (sem_id == -1)
		{
			fprintf(stderr, "%s\n", "semget error");
			error_exit();
		}
		unsigned short int sem_vals[1] = {0};
		sem_arg.array = sem_vals;
		if (semctl(sem_id,0,SETALL,sem_arg)==-1)
		{
			fprintf(stderr, "%s\n", "semctl error");
			error_exit();
		}

		sb[0].sem_flg = 0;
		

		while(flag == 0){pause();}
		flag = 0;

		printf("shm_id = %d\n",shm_id);
		sigqueue(chid,SIGUSR1,(const union sigval)shm_id);

		while(flag == 0){pause();}
		flag = 0;

		printf("sem_id = %d\n",sem_id);
		sigqueue(chid,SIGUSR1,(const union sigval)sem_id);


		int read;
		printf("%s", "input nuber of values : " );
		scanf("%d",&read);
		printf("\n");
		if (read > buf_size)
		{
			fprintf(stderr, "%s\n", "size error");
			error_exit();
		}

		while(1){
			for (int i = 0; i < read; ++i)
			{
				printf("arr[%d] = ", i);
				scanf("%d",&shm_buf[i]);
				printf("\n");
			}

			//sigqueue(chid,SIGUSR1,(const union sigval)read);
			/*
			while(flag == 0){pause();}
			flag = 0;
			*/
			sb[0].sem_num = 0;
			sb[0].sem_op = read;
			semop(sem_id,sb,1);

			sb[0].sem_num = 0;
			sb[0].sem_op = 0;
			semop(sem_id,sb,1);

			printf("Summ = %d\n", shm_buf[0]);
		}
		
	}
	else
	{
		execl("child",NULL);
	}
	return 0;
}