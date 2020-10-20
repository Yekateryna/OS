main: sub
	gcc -o "main" main.c -lm
sub:
	gcc -o "sub" sub.c -lm