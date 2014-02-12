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

/** 
* Estructura de un Nodo, compuesto por un identificador ID
*/
typedef struct _nodo {
    /** Identificador unico que caracteriza al nodo */
    char *ID;
} *nodo;


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
nodo newNodo(char *ID);

/**
* Funcion de comparacion entre dos estructuras de tipo nodo.
* Retorna 1 si ysolo si ambos nodos comparten exactamente el mismo identificador 
* @param x es el nodo a ser comparado con el nodo y
* @param y es el nodo a ser comparado con el nodo x
* @return 1, si los nodos son identicos, 0 en caso contrario
*/
int nodoEquals(nodo x, nodo y);

/**
* Representa una estructura de tipo nodo en forma de cadena
* de caracteres y la imprime en pantalla.
* @param x es el nodo a ser representado e impreso en pantalla
*/
void nodoPrint(nodo x);

/**
* Destruccion de una estructura de tipo nodo. Se libera la memoria
* ocupada por dicha estructura
* @param x es el nodo a ser liberado
*/
void freeNodo(nodo x);

#endif
