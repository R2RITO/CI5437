#ifndef FILE_FIBOHEAP
#define FILE_FIBOHEAP
#include "node.h"

typedef int (*funCompare)(void *a, void *b);

typedef struct _fiboheap {
    int  size;
    node min;
    funCompare compare; 
} *fiboheap;

// La funcion funciona asi:
// Si a es menor que b entonces devuelve negativo
// Si a es igual a b entonces devuelve 0
// Si a es mayor que b entonces devuelve positivo
fiboheap make_fib_heap(int (*c)(void *a, void *b));

void fib_heap_insert(fiboheap f, void *val);

fiboheap fib_heap_union(fiboheap a, fiboheap b);

node fib_heap_extract_min(fiboheap f);

#endif
