#ifndef FILE_FIBOHEAP
#define FILE_FIBOHEAP
#include "node.h"

/* Tipo de la funcion de comparacion */
/* La funcion hace lo siguiente:
 *  - Si 'a' es menor que 'b' entonces devuelve negativo
 *  - Si 'a' es igual a 'b' entonces devuelve 0
 *  - Si 'a' es mayor que 'b' entonces devuelve positivo
 */
typedef int (*funCompare)(void *a, void *b);

/* Estructura para un heap de fibonacci */
typedef struct _fiboheap {
    int  size;          // Numero de nodos en el heap
    node min;           // Apuntador al minimo de los elementos del heap
    funCompare compare; // Funcion para comparar entre elementos del heap
} *fiboheap;

/* FUNCION: make_fib_heap
 * DESC   : Crea un heap de fibonacci vacio
 * c      : Funcion de comparacion para comparar los elementos del heap
 * RETORNA: Un apuntador al nuevo heap de fibonacci
 */
fiboheap make_fib_heap(int (*c)(void *a, void *b));

/* FUNCION: fib_heap_insert
 * DESC   : Inserta un elemento en el heap de fibonacci
 * f      : Es el heap en donde se insertara el elemento
 * val    : Es el apuntador al objeto a insertar en el heap
 */
void fib_heap_insert(fiboheap f, void *val);

/* FUNCION: fib_heap_union
 * DESC   : Crea un nuevo heap de fibonacci resultado de unir dos
            heaps de fibonacci
 * a y b  : heaps de fibonacci, operandos de la union
 * RETORNA: Un nuevo heap de fibonacci que es la union de a y b
 */
fiboheap fib_heap_union(fiboheap a, fiboheap b);

/* FUNCION: fib_heap_extract_min
 * DESC   : Funcion que extrae el minimo del heap de fibonacci
 * f      : Heap del cual se va a extraer
 * RETORNA: El nodo que contiene el minimo elemento del heap
 */
void* fib_heap_extract_min(fiboheap f);

/* FUNCION: fib_heap_free
 * DESC   : Funcion que destruye un heap de fibonacci
 * f      : Heap a destruir
 */
void fib_heap_free(fiboheap f);
#endif
