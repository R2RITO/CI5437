#ifndef FILE_NODOS
#define FILE_NODOS

#include "lista.h"

typedef char action;

typedef struct nodo_struct *nodo;

typedef struct nodo_struct {

    /* Estado representado por el nodo */
    state estado;
    /* Accion utilizada para llegar al nodo */
    action a;
    /* Costo para llegar de la raiz al nodo */
    int g;
    /* Padre del nodo */
    nodo parent;
    /* Bit para indicar si esta cerrado. */
    int cerrado;

} *nodo;

int cost(state s, action a);

/* Crear el nodo raiz */
nodo make_root_node(state s);


/* Crear un nodo */
nodo make_node(nodo n, action a, state s);


/* Extraer el camino desde el nodo hasta la raiz */
list extract_solution(nodo n);

int compare_nodo(void *x, void *y);



#endif
