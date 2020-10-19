#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char const *argv[])
{
	int status;
	if (!fork())
	{
		execlp("ls","ls",NULL);
	}
	
	sleep(10);
	system("ps");
	sleep(5);
	printf("%s\n", "After wait");
	wait(&status);
	system("ps");

	return 0;
}