#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <fcntl.h>
#include <signal.h>


int flag = 0;
static void handler(int signo)
{
	if (signo == SIGUSR1)
	{
		flag = 1;
	}
}
int main(int argc, char const *argv[])
{
	if (signal(SIGUSR1,handler)==SIG_ERR)
	{
		fprintf(stderr, "%s\n", "signal error");
	}
	int fd_p;
	int fd_ch;
	size_t size;

	char name_p[] = "parent.fifo";
	char name_ch[] = "child.fifo";

	char buf[256];
	umask(0);
	while(flag == 0)
	{
		pause();
	}

	if (fd_p=open(name_p,O_RDONLY)<0)
	{
		fprintf(stderr, "%s\n","error child: p open" );
	}
	
	while(read(fd_p,buf,256)==0);

	for (int i = 0; i < 256; ++i)
	{
		buf[i] = toupper(buf[i]);
	}
	if (fd_p=open(name_ch,O_WRONLY)<0)
	{
		fprintf(stderr, "%s\n","error child ch open" );
	}
	size = write(fd_ch,buf,256);
	close(fd_p);
	close(fd_ch);
}
