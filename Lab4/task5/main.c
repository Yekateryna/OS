#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <getopt.h>
#include <unistd.h>
#include <sys/wait.h>

void print_info();
void my_sys(char* str);

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
			my_sys(buffer);
		}
	}
	return 0;
}


void print_info()
{
	printf("%s\n","-h or --help get help page");
	printf("%s\n", "-b or --buffer set buffer size");
}

void my_sys(char* str)
{
	str[strlen(str)-1] = ' ';
	pid_t pid = fork();
	if (pid == 0)
	{
		int i = 1;
		char* kvarg[16];
		char* istr = strtok(str," ");
		while(istr != NULL)
		{
			kvarg[i-1] = istr;
			istr = strtok(NULL," ");
			i+=1;
		}

		for (int o = i-1; o < 16; ++o)
		{
			kvarg[o]=NULL;
		}

		if (kvarg[0][0] == '.')
		{
			execv(kvarg[0],kvarg);	
		}
		else
		{
			char path[256] = {};
			strcat(path,"/bin/");
			strcat(path,kvarg[0]);
			execv(path,kvarg);
		}
		
	}
	else if(pid > 0)
	{
		if (wait(NULL) == -1)
		{
			printf("%s\n","Error wait" );
		}
		
	}
	else
	{
		printf("%s\n","Error fork");
	}
}