all: main

main: Nodo.o Arco.o
		gcc -g Nodo.o Arco.o -o main

Nodo.o: Nodo.c
		gcc -g -c Nodo.c

Arco.o: Arco.c
		gcc -g -c Arco.c

clean:
		rm -f *.o main
