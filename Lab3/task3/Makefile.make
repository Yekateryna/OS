main: main.o libhandlers.a
	gcc -o main main.o -L. -lhandlers -lm

main.o: main.c handlers.h
	gcc -c main.c

libhandlers.a: handlers.o
	ar r libhandlers.a handlers.o
	ranlib libhandlers.a

handlers.o: handlers.c handlers.h
	gcc -c handlers.c
