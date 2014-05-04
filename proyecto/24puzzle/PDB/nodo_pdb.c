#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "state_pdb.h"
#include "nodo_pdb.h"

/* Crear el nodo raiz */
pdb_nodo pdb_make_root_node(pdb_state s) {

    pdb_nodo n = malloc(sizeof(struct pdb_nodo_struct));
    (*n).estado = s;
    (*n).parent = NULL;
    (*n).a      = 0;
    (*n).g      = 0;
    return n;
}

/* Crear un nodo */
pdb_nodo pdb_make_node(pdb_nodo n, pdb_action a, pdb_state s) {

    pdb_nodo nuevo_n = malloc(sizeof(struct pdb_nodo_struct));
    (*nuevo_n).estado  = s;
    (*nuevo_n).parent  = n;
    (*nuevo_n).a       = a;
    (*nuevo_n).g       = (*n).g + (s -> cost);
    return nuevo_n;

}

/* FUNCION: pdb_free_nodo
 * DESC   : Funcion que libera un nodo
 * n      : Nodo a ser liberado
 * f      : Funcion para liberar el estado en el nodo
 */ 
void pdb_free_nodo(pdb_nodo n, void (*f)(void *a)) {
    f(n->estado);
    free(n);
}

/* FUNCION: pdb_compare_nodo
 * DESC   : Compara dos nodos
 * nx     : Primero nodo a comparar
 * ny     : Segundo nodo a comparar
 * RETORNA: Negativo si nx < ny, Cero si nx = ny, Positivo si nx > ny
 */
int pdb_compare_nodo(void *nx, void *ny) {
    pdb_nodo x = (pdb_nodo) nx;
    pdb_nodo y = (pdb_nodo) ny;
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
