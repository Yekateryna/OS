#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <fcntl.h>
#include <signal.h>


int main(int argc, char const *argv[])
{
	char* parent = "parent.fifo";
	char* child = "child.fifo";
	int fd_p, fd_ch;

	if ((fd_p=open(parent,O_RDONLY))<0)
	{
		fprintf(stderr, "%s\n","Child: fd_p open error" );
	}
	if ((fd_ch=open(child,O_WRONLY))<0)
	{
		fprintf(stderr, "%s\n","Child: fd_ch open error" );
	}

	char str[256];
	
	read(fd_p,str,256);

	for (int i = 0; i < strlen(str); ++i)
	{
		str[i] = toupper(str[i]);
	}

	write(fd_ch,str,256);
	close(fd_ch);
	close(fd_p);

	return 0;	
}

