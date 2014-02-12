/**
* @file
* @author  Arturo Voltattorni, Fernando D'agostino & Oswaldo Jimenez 
*
* @section Descripcion
*
* Definicion y prototipos del Tipo abstracto de datos Nodo.
*/

#ifndef FILE_NODO
#define FILE_NODO

#include <stdio.h>
#include <stdlib.h>

/** 
* Estructura de un Nodo, compuesto por un identificador ID
*/
typedef struct _nodo {
    /** Contenido del nodo definido de forma generica*/
    void  *elemento;
    
} *nodo;


/******************************************************************************/
/*********************** MANAGER DEL TAD NODO *********************************/
/******************************************************************************/

/**
* Creacion de un nodo. Se hace reserva de la memoria de la estructura nodo y
* se inicializa su contenido 'elemento'
* @param elem es el elemento alojado en el nodo 
* @return res, estructura de datos del tipo nodo creado
*/
nodo newNodo(void* elem);

/**
* Funcion de comparacion entre dos estructuras de tipo nodo.
* Retorna 1 si ysolo si ambos nodos comparten exactamente el mismo identificador 
* @param x es el nodo a ser comparado con el nodo y
* @param y es el nodo a ser comparado con el nodo x
* @param comparador es la funcion de comparacion entre los nodos x y
* @return 1, si los nodos son identicos, 0 en caso contrario
*/
int nodoEquals(nodo x, nodo y,int (*comparador) (void *,void *));

/**
* Representa una estructura de tipo nodo en forma de cadena
* de caracteres y la imprime en pantalla.
* @param x es el nodo a ser representado e impreso en pantalla
* @param impresor es la funcion de impresion del elemento en el nodo
*/
void nodoPrint(nodo x,void *(*impresor) (void *));

/** 
* Destruccion de una estructura de tipo nodo. Se libera la memoria
* ocupada por dicha estructura
* @param x es el nodo a ser liberado
* @param destructor es la funcion empleada para liberar el contenido de x
*/
void freeNodo(nodo x,void *(*destructor) (void *));

#endif
