#ifndef FILE_NODOS
#define FILE_NODOS

#include "lista.h"

typedef char action;

typedef struct nodo_struct *nodo;

typedef struct nodo_struct {
    /* Padre del nodo */
    nodo parent;
    /* Estado representado por el nodo */
    state estado;
    /* Costo para llegar de la raiz al nodo */
    unsigned int g : 8;
    /* Accion utilizada para llegar al nodo */
    action a;
    
} *nodo;


int cost(state s, action a);

/* Crear el nodo raiz */
nodo make_root_node(state s);


/* Crear un nodo */
nodo make_node(nodo n, action a, state s);


/* Extraer el camino desde el nodo hasta la raiz */
list extract_solution(nodo n);



/* FUNCION: free_nodo
 * DESC   : Funcion que libera un nodo
 * n      : Nodo a ser liberado
 * f      : Funcion para liberar el estado en el nodo
 */ 
void free_nodo(nodo n, void (*f)(void *a));


/* FUNCION: compare_nodo 
 * DESC   : Compara dos nodos
 * x      : Primer nodo a comparar
 * y      : Segundo nodo a comparar
 * RETORNA: Positivo si x > y, Cero si x = y, Negativo si x < y
 */
int compare_nodo(void *nx, void *ny);



#endif
