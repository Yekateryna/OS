#ifndef _ARRAYLIST_H_
#define _ARRAYLIST_H_

struct nodeList
{
	double data;
	struct nodeList* next;	
};

struct nodeList* init(double data);
void add(struct nodeList* head, double data);
void printList(struct nodeList* head);
int size(struct nodeList* head);
void insert(struct nodeList* head, int index, double data);
void removeItem(struct nodeList* head, int index);
void set(struct nodeList* head, int index, double data);
double get(struct nodeList* head, int index);
void clean(struct nodeList* head);


#endif