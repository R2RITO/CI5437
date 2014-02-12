/**
* @file
* @author  Arturo Voltattorni, Fernando D'agostino & Oswaldo Jimenez 
*
* @section Descripcion
*
* Especificacion e implementacion del Tipo abstracto de datos Nodo.
*/

#include "Nodo.h"

/******************************************************************************/
/*********************** MANAGER DEL TAD NODO *********************************/
/******************************************************************************/

/**
* Creacion de un nodo. Se hace reserva de la memoria de la estructura nodo y
* se inicializa su contenido 'elemento'
* @param elem es el elemento alojado en el nodo
* @return res, estructura de datos del tipo nodo creado
*/
nodo newNodo(void* elem) {
                         
    nodo res = malloc(sizeof(struct _nodo));
    res -> elemento = elem;
    return res;
}

/**
* Funcion de comparacion entre dos estructuras de tipo nodo.
* Retorna 1 si ysolo si ambos nodos comparten exactamente el mismo identificador 
* @param x es el nodo a ser comparado con el nodo y
* @param y es el nodo a ser comparado con el nodo x
* @param comparador es la funcion de comparacion entre los nodos x y
* @return 1, si los nodos son identicos, 0 en caso contrario
*/
int nodoEquals(nodo x, nodo y,int (*comparador) (void *,void *)) {
    return comparador(x,y);
}

/**
* Representa una estructura de tipo nodo en forma de cadena
* de caracteres y la imprime en pantalla.
* @param x es el nodo a ser representado e impreso en pantalla
* @param impresor es la funcion de impresion del elemento en el nodo
*/
void nodoPrint(nodo x,void *(*impresor) (void *)) {
    printf("Nodo:");
    impresor(x->elemento);
}

/** 
* Destruccion de una estructura de tipo nodo. Se libera la memoria
* ocupada por dicha estructura
* @param x es el nodo a ser liberado
* @param destructor es la funcion empleada para liberar el contenido de x
*/
void freeNodo(nodo x,void *(*destructor) (void *)) {
    destructor(x->elemento);
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
