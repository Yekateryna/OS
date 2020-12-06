#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

double factor(double num)
{
	if (num == 0)
	{
		return 1;
	}
	double answ = 1;
	for(int i = 1;i<=num;i++)
	{
		answ*=i;
	}
	return answ;
}

int* erat(int n)
{
	int* begining = (int*)malloc((n+1)*sizeof(int));
	int counter = 0;
	int* current = (int*)malloc(sizeof(int));
	for (int i = 0; i < n+1; ++i)
	{
		begining[i] = i;
	}

	for (int i = 2; i < n+1; ++i)
	{
		if (begining[i] != 0)
		{
			counter++;
			int* tmp = (int*)realloc(current,counter);
			if (tmp != NULL)
			{
				current = tmp;
			}
			else
			{
				printf(stderr,"%s\n", "Out of memory");
			}
			current[counter-1] = begining[i];
			for (int o = i*i; o < n+1; o+=i)
			{
				begining[o] = 0;
			}
		}
	}
	counter++;
	int* tmp = (int*)realloc(current,counter);
	if (tmp != NULL)
	{
		current = tmp;
	}
	else
	{
		printf(stderr,"%s\n", "Out of memory");
	}
	current[counter-1] = NULL;
	free(tmp);
	free(begining);
	return current;
}

int* catalan(int n)
{
	int* current  = (int*)malloc((n+1)*sizeof(int));
	for (int i = 0; i <= n; ++i)
	{
		current[i] = factor(2*i)/(factor(i+1)*factor(i));
	}
	current[n] = NULL;
	return current;
}

int main(void)
{
	int* child1;
	int* child2;

	pthread_t tid1;
	pthread_t tid2;

	if (pthread_create(&tid1,NULL,erat,10))
	{
		printf(stderr, "%s\n", "Error!");
	}

	if (pthread_create(&tid2,NULL,catalan,15))
	{
		printf(stderr, "%s\n", "Error!");
	}

	pthread_join(tid1,&child1);
	pthread_join(tid2,&child2);

	printf("%s\n", "Simples :");
	for (int i = 0;child1[i] != NULL; ++i)
	{
		if (i%10 == 0 && i != 0)
		{
			printf("\n");
		}
		printf("%d ", child1[i]);
	}
	printf("\n");
	printf("%s\n", "Catalan's :");
	for (int i = 0;child2[i] != NULL; ++i)
	{
		if (i%10 == 0 && i != 0)
		{
			printf("\n");
		}
		printf("%d ", child2[i]);
	}
	printf("\n");
	return 0;
}