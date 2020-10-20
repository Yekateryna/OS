#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <math.h>


int main(int argc, char const *argv[])
{
	if (argc<3)
	{
		return -1;
	}
	srand(time(NULL));

	int n = atoi(argv[1]);
	int r = atoi(argv[2]);
	int counter = 0;
	int dot_x = 0;
	int dot_y = 0;

	for (int i = 0; i < n; ++i)
	{
		dot_x = rand() % (2*r+10);
		dot_y = rand() % (2*r+10);
		//printf("%d %d\n",dot_x,dot_y);
		if (dot_x>=0 && dot_x<=2*r && dot_y>=0 && dot_y<=2*r)
		{
			counter+=1;
		}
	}
	printf("%d\n", counter);
	return counter;
}