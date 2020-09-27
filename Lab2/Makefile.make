main: main.o libenv.a
	gcc -o main main.o -L. -lenv -lm

main.o: main.c env.h
	gcc -c main.c

libenv.a: env.o
	ar r libenv.a env.o
	ranlib libenv.a

env.o: env.c env.h
	gcc -c env.c
