#ifndef FILE_NODO
#define FILE_NODO

typedef struct _nodo {
    char *ID;
} *nodo;

nodo newNodo(char *ID);

int nodoEquals(nodo x, nodo y);

void nodoPrint(nodo x);

void freeNodo(nodo x);


#endif
