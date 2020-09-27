#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "mathPoint.h"



double dist(struct mathPoint a, struct mathPoint b)
{
	return sqrt(pow(b.x-a.x,2)+pow(b.y-b.x,2));
}

void printArr(struct mathPoint* arr, int count){
	printf("________________________________________\n");
	for (int i = 0; i < count; ++i)
	{
		printf("Point%d(x=%f, y=%f, weight=%f)\n",i,arr[i].x,arr[i].y,arr[i].weight);
	}
	printf("________________________________________\n");
}

int searchSmall(struct mathPoint* arr, int count)
{
	int min = 0;
	for (int i = 1; i < count; ++i)
	{
		if(arr[min].weight > arr[i].weight)
		{
			min = i;
		}
	}
	return min;
}