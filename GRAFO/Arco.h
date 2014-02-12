#ifndef FILE_ARCO
#define FILE_ARCO

typedef struct _arco {

    nodo src;
    nodo dst;

} *arco;


arco newArco(nodo a, nodo b);

int arcoEquals(arco x, arco y);

void printArco(arco x);

void freeArco(arco x);


#endif
