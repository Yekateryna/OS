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
	setbuf(stdout,NULL);
	umask(0);
	char* parent = "parent.fifo";
	char* child = "child.fifo";

	if (mkfifo(parent,S_IFIFO|0666)<0)
	{
		fprintf(stderr, "%s\n", "mkfifo parent error");
	}
	if (mkfifo(child,S_IFIFO|0666)<0)
	{
		fprintf(stderr, "%s\n", "mkfifo child error");
	}

	int fd_p, fd_ch;

	if ((fd_p=open(parent,O_WRONLY))<0)
	{
		fprintf(stderr, "%s\n","fd_p open error" );
	}
	if ((fd_ch=open(child,O_RDONLY))<0)
	{
		fprintf(stderr, "%s\n","fd_ch open error" );
	}

	char str[256];
	char str1[256];
	scanf("%s",str);
	//printf("%s\n", str);

	write(fd_p,str,256);
	read(fd_ch,str1,256);
	printf("%s\n",str1 );

	close(fd_p);
	close(fd_ch);
	return 0;
}