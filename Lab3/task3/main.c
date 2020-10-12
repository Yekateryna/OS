#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "handlers.h"

int main(int argc, char const *argv[])
{

	if (argc>1)
	{
		int read = atoi(argv[1]);
		if (read>32 || read<0)
		{
			printf("%s\n","Invalid value");
		}
		else
		{
			for(int i=0;i<read;i+=1)
			{
				atexit(handler_arr[i]);
			}
		}

	}
	return 0;
}