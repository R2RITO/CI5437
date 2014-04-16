#include <stdio.h>
#include "lista.h"

typedef char action;
typedef void* state;

typedef struct nodo_struct* nodo;

struct nodo_struct {

    /* Estado representado por el nodo */
    state estado;
    /* Accion utilizada para llegar al nodo */
    action a;
    /* Costo para llegar de la raiz al nodo */
    int g;
    /* Padre del nodo */
    struct nodo_struct* parent;
    /* Bit para indicar si esta cerrado. */
    int cerrado;

};


/* Calcular el costo de utilizar la accion a desde
   el nodo n */

int cost(state s, action a) {

    /* Esta funcion debe retornar el costo de utilizar
       la accion a desde el estado s, para el 15-puzzle
       es constante */

    return 1;

}


/* Crear el nodo raiz */
nodo make_root_node(state s) {

    nodo n;
    (*n).estado = s;
    (*n).parent = NULL;
    (*n).a      = 0;
    (*n).g      = 0;

    return n;
}

/* Crear un nodo */
nodo make_node(nodo n, action a, state s) {

    nodo nuevo_n;
    (*nuevo_n).estado  = s;
    (*nuevo_n).parent  = n;
    (*nuevo_n).a       = a;
    (*nuevo_n).g       = (*n).g + cost((*n).estado,a);

    return nuevo_n;

}

/* Extraer el camino desde el nodo hasta la raiz */
list extract_solution(nodo n) {

    list q = newList();
    
    while ((*n).parent != NULL) {
        addListElem(q,&((*n).a));
        n = (*n).parent;
    }

    return q;
}


main(int argc, char *argv[]) {
    
    printf("Main\n");

}
