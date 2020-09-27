#include <stdio.h>
#include <stdlib.h>
#include "arrayList.h"

struct nodeList* init(double data)
{
	struct nodeList* head = (struct nodeList*)malloc(sizeof(struct nodeList));
	head->data = data;
	head->next = NULL;
	return head;
}

void add(struct nodeList* head, double data)
{
	struct nodeList* tmp = head;
	while(tmp->next != NULL){
		tmp = tmp->next;
	}
	struct nodeList* newNode = (struct nodeList*)malloc(sizeof(struct nodeList));
	newNode->data = data;
	newNode->next = NULL;
	tmp->next = newNode;
}

void printList(struct nodeList* head)
{
	struct nodeList* tmp = head; 
	while(tmp != NULL)
	{
		printf("%f \n", tmp->data);
		tmp=tmp->next;
	}	
}

int size(struct nodeList* head)
{
	int counter = 0;
	struct nodeList* tmp = head;
	while(tmp != NULL)
	{
		tmp=tmp->next;
		counter+=1;
	}
	return counter;
}

void insert(struct nodeList* head, int index, double data)
{
	if(index >= size(head))
	{
		add(head,data);
	}
	else
	{
		struct nodeList* newNode = (struct nodeList*)malloc(sizeof(struct nodeList));
		newNode->data = data;
		struct nodeList* tmp = head;
		for (int i = 0; i < index-1; ++i)
		{
			tmp=tmp->next;
		}
		newNode->next = tmp->next;
		tmp->next = newNode;
		
	}
}

void removeItem(struct nodeList* head, int index)
{
	if(index < size(head))
	{
		struct nodeList* tmp = head;
		for (int i = 0; i < index-1; ++i)
		{
			tmp=tmp->next;
		}
		tmp->next = tmp->next->next;
		tmp = tmp->next;
		free(tmp);
	}
}

void set(struct nodeList* head, int index, double data)
{
	if(index < size(head))
	{
		struct nodeList* tmp = head;
		for (int i = 0; i < index; ++i)
		{
			tmp=tmp->next;
		}
		tmp->data = data;
	}
}

double get(struct nodeList* head, int index)
{
	if (index < size(head))
	{
		struct nodeList* tmp = head;
		for (int i = 0; i < index; ++i)
		{
			tmp=tmp->next;
		}
		return tmp->data;
	}
}

void clean(struct nodeList* head)
{
	struct nodeList* tmp = head;
	struct nodeList* tmp1; 
	while(tmp != NULL)
	{
		tmp1 = tmp->next;
		free(tmp);
		tmp = tmp1;
	}
	free(tmp);
	free(tmp1);

}