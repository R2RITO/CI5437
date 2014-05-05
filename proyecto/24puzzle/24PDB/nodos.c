#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "lista.h"
#include "state.h"
#include "nodos.h"


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

    nodo n = malloc(sizeof(struct nodo_struct));
    (*n).estado = s;
    (*n).parent = NULL;
    (*n).a      = 0;
    (*n).g      = 0;
    return n;
}

/* Crear un nodo */
nodo make_node(nodo n, action a, state s) {

    nodo nuevo_n = malloc(sizeof(struct nodo_struct));
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

/* FUNCION: free_nodo
 * DESC   : Funcion que libera un nodo
 * n      : Nodo a ser liberado
 * f      : Funcion para liberar el estado en el nodo
 */ 
void free_nodo(nodo n, void (*f)(void *a)) {
    f(n->estado);
    free(n);
}



