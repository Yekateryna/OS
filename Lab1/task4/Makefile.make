main: main.o libarraylist.a
	gcc -o main main.o -L. -larraylist -lm

main.o: main.c arrayList.h
	gcc -c main.c

libarraylist.a: arrayList.o
	ar r libarraylist.a arrayList.o
	ranlib libarraylist.a

arrayList.o: arrayList.c arrayList.h
	gcc -c arrayList.c
