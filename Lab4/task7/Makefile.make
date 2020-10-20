main: child
	gcc -o main main.c

child:
	gcc -o child child.c -lm