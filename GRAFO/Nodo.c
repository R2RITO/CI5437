/**
* @file
* @author  Arturo Voltattorni, Fernando D'agostino & Oswaldo Jimenez 
*
* @section Descripcion
*
* Especificacion e implementacion del Tipo abstracto de datos Nodo.
*/

#include <stdio.h>
#include <stdlib.h>
#include "Nodo.h"

/******************************************************************************/
/*********************** MANAGER DEL TAD NODO *********************************/
/******************************************************************************/

/**
* Creacion de un nodo. Se hace reserva de la memoria de la estructura nodo y
* se inicializa su identificador ID
* @param ID es el identificador quien diferencia univocamente al nodo 
* de creacion del resto de los nodos que conforman un grafo
* @return res, estructura de datos del tipo arco creado
*/
nodo newNodo(char* ID) {
    nodo res = malloc(sizeof(struct _nodo));
    res -> ID = ID;
    return res;
}

/**
* Funcion de comparacion entre dos estructuras de tipo nodo.
* Retorna 1 si ysolo si ambos nodos comparten exactamente el mismo identificador 
* @param x es el nodo a ser comparado con el nodo y
* @param y es el nodo a ser comparado con el nodo x
* @return 1, si los nodos son identicos, 0 en caso contrario
*/
int nodoEquals(nodo x, nodo y) {
    return x->ID == y->ID;
}

/**
* Representa una estructura de tipo nodo en forma de cadena
* de caracteres y la imprime en pantalla.
* @param x es el nodo a ser representado e impreso en pantalla
*/
void nodoPrint(nodo x) {
    printf("Nodo: %d", x->ID);
}

/** 
* Destruccion de una estructura de tipo nodo. Se libera la memoria
* ocupada por dicha estructura
* @param x es el nodo a ser liberado
*/
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
