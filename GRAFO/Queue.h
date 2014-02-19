/**
* @file
* @author  Arturo Voltattorni, Fernando D'agostino & Oswaldo Jimenez 
*
* @section Descripcion
*
* Definicion y prototipos del TAD Cola 'queue'
*/

#ifndef FILE_QUEUE
#define FILE_QUEUE

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/**
 *  Estructura Dinamica auxiliar de la cola 'QUEUE_NODE'
 *  compuesto por un puntero a su contenido
 *  un puntero a la siguiente estructura 'queue_node' de la cola
 * y un puntero a la estructura 'queue_node' anterior.
 * Implementa una lista doblemente enlazada
 */
typedef struct queue_node {
	    /** Punterio al contenido a ser almacenado por el box */
        void  *contenido; 
        /** Puntero a la siguiente estructura box */
        struct queue_node *next; 
        /** Puntero a la estructura box anterior */
        struct queue_node *front;
} QUEUE_NODE;

/**
 *  Estructura cola dinamica 'queue'
 *  Sus atributos son el tamanio de la cola
 *  punteros aL tope 'top' y al fondo 'bottom'
 */
typedef struct queue {
	    /** Tamaño de la cola */
        int  size; 
        /** Puntero al tope de la cola */
        QUEUE_NODE *top; 
        /** Puntero al fondo de la cola */
        QUEUE_NODE *bottom; 
} QUEUE;

/** 
* Elimina una estructura dinamica cola, se
* libera su espacio de memoria.
* @param q la cola a liberar
*/
void erase_queue(QUEUE* q);

/** 
* Crea una estructura dinamica cola, se
* reseva su espacio de memoria
* @return La cola creada 
*/
QUEUE* create_queue(void);

/** 
* Indica si la cola no contiene elementos
* @param q Estructura cola de entrada
* @return 1 si la cola esta vacia, 0 en caso contrario
*/
int isEmpty(QUEUE *q);

/** 
* Retorna la cardinalidad de la cola
* @param q Estructura cola de entrada
* @return Tamanio de la cola entrante
*/
int getSize(QUEUE *q);

/** 
* Encola un elemento en la cola
* @param q Cola a encolar
* @param elem contenido a encolar
*/
void enqueue(QUEUE *q, void *nodo);

/** 
* Desencola un elemento de la cola
* @param q Cola a desencolar
*/
void dequeue(QUEUE *q);

/** 
* Se eliminan y liberan los elementos de la cola
* y queda como recien creada
* @param q Cola a resetear
*/
void clear(QUEUE *q);

/** 
* Impresion de los elementos en la cola, desde el tope hacia el fondo,
* en esa direccion.
* @param q Cola a imprimir
*/
void print_queue_from_top(QUEUE *q,void *(*impresor) (void *));

/** 
* Impresion de los elementos en la cola, desde el fondo hacia el tope,
* en esa direccion.
* @param q Cola a imprimir
*/
void print_queue_from_bottom(QUEUE *q,void *(*impresor) (void *));

#endif /* QUEUE_H */
