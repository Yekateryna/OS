#include "mathPoint.h"

int main(void)
{
	int N = 0;
	int count = 0;
	printf("Input number of points\n");
	scanf("%d",&N);

	count = N;

	double summ=0;

	struct mathPoint* points = (struct mathPoint*)malloc(N*sizeof(struct mathPoint));

	for (int i = 0; i < count; ++i)
	{
		points[i].x = rand()%30;
		points[i].y = rand()%30;
		points[i].weight = rand()%30;
		summ+=points[i].weight;
	}
	printArr(points,count);
	printf("---Summ = %f---\n",summ);

	for (int i = 0; i < N-1; ++i)
	{
		int min = searchSmall(points,count);
		int nearist = -1;
		int nearistInd = 0;
		for (int i = 0; i < count; ++i)
		{
			if(i != min){
				double tmp = dist(points[min],points[i]);
				if(nearist == -1 || tmp < nearist){
					nearist = tmp;
					nearistInd = i;
				}
			}
		}
		points[nearistInd].weight+=points[min].weight;
		
		count-=1;

		for (int i = min; i < count; ++i)
		{
			points[i] = points[i+1];
		}
		
		points = (struct mathPoint*)realloc(points,count*sizeof(struct mathPoint));
		printArr(points,count);


	}

	return 0;
}