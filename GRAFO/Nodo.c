#include <stdio.h>
#include <stdlib.h>
#include "Nodo.h"

nodo newNodo(int ID) {
    nodo res = malloc(sizeof(struct _nodo));
    res -> ID = ID;
    return res;
}

int nodoEquals(nodo x, nodo y) {
    return x->ID == y->ID;
}

void nodoPrint(nodo x) {
    printf("Nodo: %d", x->ID);
}

void freeNodo(nodo x) {
    free(x);
}

/*main(int argc, char *argv[]) {
    nodo a = newNodo(3);
    nodo b = newNodo(3);
    nodoPrint(a);
    nodoPrint(b);
    printf("%d\n",nodoEquals(a,b));
    freeNodo(a);
    freeNodo(b);
}*/
