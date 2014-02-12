/**
* @file
* @author  Arturo Voltattorni, Fernando D'agostino & Oswaldo Jimenez 
*
* @section Descripcion
*
* Definicion y prototipos del Tipo abstracto de datos Arco.
*/

#ifndef FILE_ARCO
#define FILE_ARCO

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

/** 
* Estructura de un Arco, compuesto por un nodo fuente src
* y un nodo destino dst
*/
typedef struct _arco {   
    /** Nodo fuente del arco */
    nodo src;
    /** Nodo destino del arco */
    nodo dst;

} *arco;

/******************************************************************************/
/*********************** MANAGER DEL TAD ARCO *********************************/
/******************************************************************************/


/** 
* Creacion de un arco. Se hace reserva de la memoria de la estructura arco y
* se inicializan los valores correspondientes a los nodos fuente (src) y
* destino (dst) que lo componen.
* @param fuente es el nodo fuente del arco creado
* @param destino es el nodo de destino del arco creado
* @return res, estructura de datos del tipo arco
*/
arco newArco(nodo a, nodo b);

/**
* Funcion de comparacion entre dos estructuras de tipo arco.
* Retorna 1 si y solo si ambos arcos comparten exactamente el mismo nodo
* fuente y el mismo nodo destino 
* @param x es el arco a ser comparado con el arco y
* @param y es el arco a ser comparado con el arco x
* @param comparador es la funcion de comparacion entre los arcos x y
* @return 1, si los arcos son identicos, 0 en caso contrario
*/
int arcoEquals(arco x, arco y,int (*comparador) (void *,void *));

/**
* Representa una estructura de tipo arco en forma de cadena
* de caracteres y la imprime en pantalla. Se vale de la funcion de impresion
* asociada a la estructura de tipo nodo  
* @param x es el arco a ser representado e impreso en pantalla
* @param impresor es la funcion de impresion empleada por los nodos del arco
*/
void printArco(arco x,void *(*impresor) (void *));

/**
* Destruccion de una estructura de tipo arco. Se libera la memoria
* ocupada por dicha estructura
* @param x es el arco a ser liberado
*/
void freeArco(arco x);

#endif
