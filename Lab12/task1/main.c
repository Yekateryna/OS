#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char const *argv[])
{
	int fd_p[2];
	int fd_ch[2];
	size_t size;

	char buf[256];

	if (pipe(fd_p)<0)
	{
		fprintf(stderr, "%s\n", "fd_p error");
	}
	if (pipe(fd_ch)<0)
	{
		fprintf(stderr, "%s\n","fd_ch error");
	}
	if (fork())
	{
		scanf("%s",buf);
		size = write(fd_p[1],buf,256);
		size = read(fd_ch[0],buf,256);
		printf("%s\n",buf);
		close(fd_p[1]);
		close(fd_ch[0]);

	}
	else
	{
		size = read(fd_p[0],buf,256);
		for (int i = 0; i < strlen(buf); ++i)
		{
			buf[i] = toupper(buf[i]);
		}
		size = write(fd_ch[1],buf,256);
		close(fd_p[0]);
		close(fd_ch[1]);
	}
	return 0;
}