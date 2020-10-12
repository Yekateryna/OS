#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>

void set_file_name(char*);

int main(int argc, char const *argv[])
{
	extern char* optarg;
	char* optstring = "f:n:";
	struct option long_opt[] = {
		{"file",1,0,'f'},
		{"number",1,1,'n'},
		{NULL,0,NULL,0}
	};

	int c;
	int number;

	while((c = getopt_long(argc,argv,optstring,long_opt,NULL))!=-1)
		{
			switch(c)
			{
				case 'f':
					set_file_name(optarg);
				break;

				case 'n':
					number = atoi(optarg);
				break;
			}
		}
	
	for(int i=1;i<=number;i+=1)
	{
		char buffer[10];
		char str[256]={};
		snprintf(buffer,10,"%d",i);
		strcat(str,"./sub -n ");
		strcat(str,buffer);
		printf("%s\n",str );
		system(str);
	}

	return 0;
}

void set_file_name(char* name)
{
	char str[256]={};
	strcat(str,"FILE_NAME=");
	strcat(str,name);
	putenv(str);
}