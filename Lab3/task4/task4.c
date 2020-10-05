#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <getopt.h>
#include <unistd.h>

void print_info();

int main(int argc, char const *argv[])
{
	int buffer_size = 127;

	if (argc != 1)
	{
		extern char* optarg;
		char* optstring = "hb:";
		int c;
		struct option long_opt[] = {
			{"help",0,0,'h'},
			{"buffer",1,0,'b'},
			{NULL,0,NULL,0}
		};
		while((c = getopt_long(argc,argv,optstring,long_opt,NULL))!=-1)
		{
			switch(c)
			{
				case 'h':
					print_info();
				break;

				case 'b':
					buffer_size = atoi(optarg);
				break;
			}
		}
	}
	char* stop_msg = "stop\n";

	char* buffer = (char*)malloc(buffer_size*sizeof(char));
	while(1)
	{
		printf("%s$>",getlogin());
		getline(&buffer,&buffer_size,stdin);
		if (strcmp(buffer,stop_msg) == 0)
		{
			printf("Wait 3 seconds...\n");
			free(buffer);
			system("sleep 3");
			system("clear");
			break;
		}
		else
		{
			system(buffer);
		}
	}
	return 0;
}


void print_info()
{
	printf("%s\n","-h or --help get help page");
	printf("%s\n", "-b or --buffer set buffer size");
}