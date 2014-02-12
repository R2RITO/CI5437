#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "Nodo.h"
#include "Arco.h"

arco newArco(nodo a, nodo b) {
    arco res = malloc(sizeof(struct _arco));
    res -> src = a;
    res -> dst = b;
    return res;
}

int arcoEquals(arco x, arco y) {
    nodo srcx = x -> src;
    nodo dstx = x -> dst;
    nodo srcy = y -> src;
    nodo dsty = y -> dst;
    return (nodoEquals(srcx, srcy)) &&
           (nodoEquals(dstx, dsty)); 
}

void printArco(arco x) {
    printf("(");
    nodoPrint(x -> src);
    printf(" , ");
    nodoPrint(x -> dst);
    printf(")\n");
}

void freeArco(arco x) {
    free(x);
}


unsigned long sdbm(char *str) {
    
    unsigned long hash = 0;
    int c;

    while (c = *str++)
        hash = c + (hash << 6) + (hash << 16) - hash;

    return hash;
}

main() {

    nodo nodo1 = newNodo(0);
    nodo nodo2 = newNodo(3);
    nodo nodo3 = newNodo(4);
    nodo nodo4 = newNodo(99);

    arco arquito = newArco(nodo1,nodo2);
    arco arquitoInv = newArco(nodo2,nodo1);
    arco arc = newArco(nodo1,nodo3);
     
    printArco(arquito);
    printf("\n Salto de linea \n");
    printArco(arquitoInv);
    printArco(arc);
    printf("\n Salto de linea \n");

    printf("Comparacion 1: %d 2: %d \n", arcoEquals(arc,arc),arcoEquals(arquito,arc));

    free(nodo1);
    free(nodo2);
    free(nodo3);
    free(nodo4);
    free(arquito);
    free(arquitoInv);
    free(arc);

    char *cosa = malloc(sizeof(10));
    strcpy(cosa,"ABCDEFGHI");

    printf("LA COSA ES: %s\n", cosa);
    printf("PRUEBALO Y VELO: %d \n", sdbm(cosa));
    printf("LA COSA ES: %s\n", cosa);
       
}
