#include "arrayList.h"

int main(void)
{
	struct nodeList* arrayList = init(1);
	add(arrayList,2);
	insert(arrayList,1,3);
	removeItem(arrayList,2);
	set(arrayList,0,4);
	printList(arrayList);
	printf("%f\n", get(arrayList,1));
	clean(arrayList);

	return 0;
}