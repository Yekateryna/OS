#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int main(int argc, char const *argv[])
{
	int current_number;
	extern char* optarg;
	char* optstring = "n:";
	int c;
	while((c=getopt(argc,argv,optstring))!=-1)
	{
		switch(c)
		{
			case 'n':
				current_number=atoi(optarg);
			break;
			case '?':
				printf("%s\n", "Error in subprogram ");
				return 0;
		}
	}

	char* base_name = getenv("FILE_NAME");
	char str[256] = {};
	if(base_name != NULL)
	{
		strcat(str,base_name);
	}
	else
	{
		strcat(str,"default_name");	
	}
	char buffer[10]={};
	snprintf(buffer,10,"%d",current_number);
	strcat(str,buffer);
	strcat(str,".txt");

	struct timespec t1;
	clock_gettime(CLOCK_REALTIME,&t1);
	srand(t1.tv_nsec);

	FILE* f = fopen(str,"w");

	for(int i=0;i<current_number;i+=1)
	{
		fprintf(f,"%f\n", (double)rand()/RAND_MAX);
	}
	fclose(f);



	return 0;
}