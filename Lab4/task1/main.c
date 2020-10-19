#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>


int main(int argc, char const *argv[])
{
	if (argc == 1)
	{
		printf("\nPID = %d\n",getpid());
		printf("PPID = %d\n",getppid());
		printf("group ID = %d\n",getpgrp());
		printf("UID = %d\n", getuid());
		printf("GID = %d\n", getgid());
		printf("eUID = %d\n", geteuid());
		printf("eGID = %d\n", getegid());
	}
	return 0;
}