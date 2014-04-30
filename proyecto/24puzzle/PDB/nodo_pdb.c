#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "state_pdb.h"
#include "nodo_pdb.h"

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
    (*nuevo_n).g       = (*n).g + (s -> cost);
    return nuevo_n;

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

/* FUNCION: compare_nodo
 * DESC   : Compara dos nodos
 * nx     : Primero nodo a comparar
 * ny     : Segundo nodo a comparar
 * RETORNA: Negativo si nx < ny, Cero si nx = ny, Positivo si nx > ny
 */
int compare_nodo(void *nx, void *ny) {
    nodo x = (nodo) nx;
    nodo y = (nodo) ny;
    int res = (x->g) - (y->g) ; 
    if (res) {
        return res;
    } else {
        return ((x->g)-(y->g));
    }
}
/*
void main() {

    printf("Hola");

}*/
