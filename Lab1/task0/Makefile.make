main: main.o libmathpoint.a
	gcc -o main main.o -L. -lmathpoint -lm

main.o: main.c mathPoint.h
	gcc -c main.c

libmathpoint.a: mathPoint.o
	ar r libmathpoint.a mathPoint.o
	ranlib libmathpoint.a

mathPoint.o: mathPoint.c mathPoint.h
	gcc -c mathPoint.c
