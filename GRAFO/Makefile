all: main

main: Nodo.o Arco.o Grafo.o
		gcc -g Nodo.o Arco.o Grafo.o -o main

Nodo.o: Nodo.c
		gcc -g -c Nodo.c

Arco.o: Arco.c
		gcc -g -c Arco.c
		
Grafo.o: Grafo.c
		gcc -g -c Grafo.c

clean:
		rm -f *.o main

