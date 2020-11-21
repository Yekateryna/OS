#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <math.h>

struct args
{
	double a;
	double b;
	double* e;
	pthread_mutex_t* mutex;
	double* I;
};

double func(double x)
{
	return (4-x*x);
}

void integr(void* arg)
{
	double n = 1000;
	struct args* tmp = (struct args*)arg;
	double a = tmp->a;
	double b = tmp->b;
	double e = *(tmp->e);
	printf("a = %f,b = %f,e = %f\n",a,b,e);

	double In = 0.0;
	double I2n = In*2;
	while(1)
	{
		double h = (b-a)/n;
		for (double x = a; x <= b; x+=h)
		{
			I2n += func(x+h/2);
		}
		I2n*=h;

		if (fabs(In - I2n)<e)
		{
			break;
		}
		else
		{
			In = I2n;
			I2n = 0.0;
			n += 100;
		}
	}
	pthread_mutex_lock(tmp->mutex);
	(*(tmp->I))+=I2n;
	pthread_mutex_unlock(tmp->mutex);
	return NULL;
}

int main(int argc, char const *argv[])
{
	double I = 0;
	double a = 0;
	double b = 2;
	double e = 1e-2;
	int n;
	if (argc==2)
	{
		n = atoi(argv[1]);
	}
	else
	{
		printf("%s\n","Invalid argv");
		return 0;
	}

	double h = (b-a)/n;
	pthread_t* pids = (pthread_t*)malloc(n*sizeof(pthread_t));
	struct args* farg = (struct args*)malloc(n*sizeof(struct args));

	pthread_mutex_t mutex;
	pthread_mutex_init(&mutex,NULL);

	for (int i = 0; i < n; ++i)
	{
		farg[i].a = a+i*h;
		farg[i].b = farg[i].a + h;
		farg[i].e = &e;
		farg[i].mutex = &mutex;
		farg[i].I = &I;
		pthread_create(&pids[i],NULL,&integr,&farg[i]);
	}
	for (int i = 0; i < n; ++i)
	{
		pthread_join(pids[i],NULL);
	}
	printf("%f\n", I);
	pthread_mutex_destroy(&mutex);
	return 0;
}