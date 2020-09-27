#include <stdlib.h>
#include <stdio.h>
#include <string.h>

extern char** environ;

void env_info()
{
 	int i = 0;
 	while(environ[i] != NULL)
 	{
 		printf("%s\n", environ[i]);
 		i+=1;
 	}
}

void get_info(char* str)
{
	char* tmp = getenv(str);
	if(tmp!=NULL)
	{
		printf("Done : %s = %s\n",str,tmp);
	}
	else
	{
		printf("%s not found",str);
	}
}

void set_value(char* str)
{
	if(putenv(str) == 0)
	{
		printf("Done : %s\n",str );
	}
}

void put(char* var,char* val)
{
	if(var != NULL)
	{
		char str[256] = {};
		strcat(str,var);
		strcat(str,"=");
		if(val != NULL)
		{
			strcat(str,val);
		}
		else
		{
			strcat(str,"NULL");
		}
		set_value(str);
	}
	else
	{
		printf("Variable not defined\n");
	}
}

void del(char* str)
{
	unsetenv(str);
}

void clear()
{
	clearenv();
}

void help()
{
	printf("environ [--option] [<arg>]\nOptions :\n");
	printf("-h or --help  Print help page\n");
	printf("-i or --info  <variable> Print value of variable\n");
	printf("-s or  --set  <variable=value>  Set value to variable\n");
	printf("-a or --assign <variable> and -v or --value <value>  Set <value> to <variable>.\n\tIf value not given, set value NULL\n");
	printf("-d or --del <variable>  Remove variable\n");
	printf("-c or --clear  Remove all variables\n");
}