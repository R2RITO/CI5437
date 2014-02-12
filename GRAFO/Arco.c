/**
* @file
* @author  Arturo Voltattorni, Fernando D'agostino & Oswaldo Jimenez 
*
* @section Descripcion
*
* Especificacion e implementacion del Tipo abstracto de datos Arco.
*/

#include "Nodo.h"
#include "Arco.h"

/******************************************************************************/
/*********************** MANAGER DEL TAD ARCO *********************************/
/******************************************************************************/

/**
* Creacion de un arco. Se hace reserva de la memoria de la estructura arco y
* se inicializan los valores correspondientes a los nodos fuente (src) y
* destino (dst) que lo componen.
* @param fuente es el nodo fuente del arco creado
* @param destino es el nodo de destino del arco creado
* @return res, estructura de datos del tipo arco creado
*/
arco newArco(nodo fuente, nodo destino) {
    arco res = malloc(sizeof(struct _arco));
    res -> src = fuente;
    res -> dst = destino;
    return res;
}

/**
* Funcion de comparacion entre dos estructuras de tipo arco.
* Retorna 1 si y solo si ambos arcos comparten exactamente el mismo nodo
* fuente y el mismo nodo destino 
* @param x es el arco a ser comparado con el arco y
* @param y es el arco a ser comparado con el arco x
* @param comparador es la funcion de comparacion entre los arcos x y
* @return 1, si los arcos son identicos, 0 en caso contrario
*/
int arcoEquals(arco x, arco y,int (*comparador) (void *,void *)) {
    nodo srcx = x -> src;
    nodo dstx = x -> dst;
    nodo srcy = y -> src;
    nodo dsty = y -> dst;
    return (nodoEquals(srcx, srcy,comparador)) &&
           (nodoEquals(dstx, dsty,comparador)); 
}

/**
* Representa una estructura de tipo arco en forma de cadena
* de caracteres y la imprime en pantalla. Se vale de la funcion de impresion
* asociada a la estructura de tipo nodo  
* @param x es el arco a ser representado e impreso en pantalla
* @param impresor es la funcion de impresion empleada por los nodos del arco
*/
void printArco(arco x,void *(*impresor) (void *)) {
    printf("(");
    nodoPrint(x -> src,impresor);
    printf(" , ");
    nodoPrint(x -> dst,impresor);
    printf(")\n");
}

/**
* Destruccion de una estructura de tipo arco. Se libera la memoria
* ocupada por dicha estructura
* @param x es el arco a ser liberado
*/
void freeArco(arco x) {
    free(x);
}

/**
* null
* @param str null
* @return unknown
*/
unsigned long sdbm(char *str) {
    
    unsigned long hash = 0;
    int c;

    while (c = *str++)
        hash = c + (hash << 6) + (hash << 16) - hash;

    return hash;
}

/**
* Main de pruebas
*
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
       
}*/
