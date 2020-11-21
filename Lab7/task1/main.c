#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <getopt.h>

long glob = 0;

void help()
{
	printf("-n or --number  Set number of incr/decr\n");
	printf("-p or --pairs Set number of threads\n");
}

void* thread_incr(void* arg)
{
	long num = *(long*)arg;
	for (int i = 0; i < num; ++i)
	{
		glob++;
	}
}

void* thread_decr(void* arg)
{
	long num = *(long*)arg;
	for (int i = 0; i < num; ++i)
	{
		glob--;
	}
}

int main(int argc, char const *argv[])
{
	if (argc <2)
	{
		help();
		return 0;
	}
	extern char* optarg;
	char* optstring = "hn:p:";

	int c;
	long num = 10000;
	int pairs = 2;
 	struct option long_opt[] = {
 		{"help",0,0,'h'},
 		{"number",1,0,'n'},
 		{"pairs",1,0,'p'},
 		{NULL,0,NULL,0}
 	};
 	while((c = getopt_long(argc,argv,optstring,long_opt,NULL))!=-1)
 	{
 			switch(c)
 			{
 				case 'h':
 					help();
 					return 0;

 				case 'n':
 					num = atoi(optarg);
 				break;

 				case 'p':
 					pairs = atoi(optarg);
 				break;

 				default:
 					help();
 					return 0;
 			}
 	}

 	pthread_t* pids = (pthread_t*)malloc(pairs*2*sizeof(pthread_t));
 	printf("glob = %ld\n", glob);
 	for (int i = 0; i <= pairs; i+=2)
 	{
 		pthread_create(&pids[i],NULL,&thread_incr,&num);
 		pthread_create(&pids[i+1],NULL,&thread_decr,&num);
 	}

 	for (int i = 0; i <= pairs; i+=2)
 	{
 		pthread_join(pids[i],NULL);
 		pthread_join(pids[i+1],NULL);
 	}
 	printf("glob = %ld\n", glob);
 	free(pids);
	return 0;
}
