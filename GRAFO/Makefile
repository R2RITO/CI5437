all: main

main: Nodo.o Arco.o Grafo.o Queue.o main.o
		gcc -g Nodo.o Arco.o Grafo.o Queue.o main.o -o main

Nodo.o: Nodo.c
		gcc -g -c Nodo.c

Arco.o: Arco.c
		gcc -g -c Arco.c
		
Grafo.o: Grafo.c
		gcc -g -c Grafo.c

Queue.o: Queue.c
		gcc -g -c Queue.c
		
main.o: main.c
		gcc -g -c main.c

clean:
		rm -f *.o main

