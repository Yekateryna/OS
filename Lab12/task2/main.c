#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <signal.h>

int main(int argc, char const *argv[])
{

	if (argc != 2)
	{
		fprintf(stderr, "%s\n", "error");
	}
	int sig = atoi(argv[1]);

	int fd_p;
	int fd_ch;
	size_t size;

	char name_p[] = "parent.fifo";
	char name_ch[] = "child.fifo";

	char buf[256];
	umask(0);
	
	if (mknod(name_ch,S_IFIFO|0666,0)<0)
	{
		fprintf(stderr, "%s\n", "error ch");
	}
	if (mknod(name_p,S_IFIFO | 0666,0)<0)
	{
		fprintf(stderr, "%s\n", "error p");
	}

	kill(sig,SIGUSR1);
	scanf("%s",buf);
	if (fd_p=open(name_p,O_WRONLY)<0)
	{
		fprintf(stderr, "%s\n","error p open" );
	}

	
	size = write(fd_p,buf,256);

	if (fd_ch=open(name_ch,O_RDONLY)<0)
	{
		fprintf(stderr, "%s\n", "error ch open");
	}

	while(read(fd_ch,buf,256)==0);
	
	printf("\n get : %s\n",buf);
	close(fd_p);
	close(fd_ch);
	return 0;
}