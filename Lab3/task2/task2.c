#include <stdlib.h>
#include <stdio.h>

int main(int argc, char const *argv[])
 {
 	if (argc > 1)
 	{
 		printf("%d\n", system(argv[1]));
 	}
 	return 0;
 } 