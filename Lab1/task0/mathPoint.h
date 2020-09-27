#ifndef _MATHPOINT_H_
#define _MATHPOINT_H_

struct mathPoint
{
	double weight;
	double x;
	double y;
};

double dist(struct mathPoint a, struct mathPoint b);
void printArr(struct mathPoint* arr, int count);
int searchSmall(struct mathPoint* arr, int count);

#endif
