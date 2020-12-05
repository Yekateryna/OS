#include <stdio.h>
#include <stdlib.h>
#include <sys/shm.h>
#include <unistd.h>
#include <signal.h>

int flag = 0;
int chid;
int* shm_buf;
int shm_id;

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

		while(flag == 0){pause();}
		flag = 0;

		printf("shm_id = %d\n",shm_id);
		sigqueue(chid,SIGUSR1,(const union sigval)shm_id);

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

			sigqueue(chid,SIGUSR1,(const union sigval)read);

			while(flag == 0){pause();}
			flag = 0;

			printf("Summ = %d\n", shm_buf[0]);
		}
		
	}
	else
	{
		execl("child",NULL);
	}
	return 0;
}