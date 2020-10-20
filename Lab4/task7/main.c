#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <wait.h>

double sq(double all,double in_target,int r)
{
	double Sp = 4*r*r;
	double S = (in_target/all)*Sp; //232
	return S;
}

int main(int argc, char const *argv[])
{
	char* rad = "10";
	int r = atoi(rad);
	int n = atoi(argv[1]);
	int in_target = 0;
	if (argc<2)
	{
		return 0;
	}
	if (!fork())
	{
		execlp("./child","child",argv[1],rad,NULL);
	}
	else
	{
		wait(&in_target);
		int target = WEXITSTATUS(in_target);
		double pi = sq(n,target,r)/(r*r);
		printf("%f\n", pi);
	}

	return 0;
}