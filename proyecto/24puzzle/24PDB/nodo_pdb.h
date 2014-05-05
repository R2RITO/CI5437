#ifndef FILE_NODOS_PDB
#define FILE_NODOS_PDB

typedef char pdb_action;

typedef struct pdb_nodo_struct *pdb_nodo;

typedef struct pdb_nodo_struct {
    /* Padre del nodo */
    pdb_nodo parent;
    /* Estado representado por el nodo */
    pdb_state estado;
    /* Costo para llegar de la raiz al nodo */
    unsigned int g : 8;
    /* Accion utilizada para llegar al nodo */
    pdb_action a;
    
} *pdb_nodo;


int pdb_cost(pdb_state s, pdb_action a);

/* Crear el nodo raiz */
pdb_nodo pdb_make_root_node(pdb_state s);


/* Crear un nodo */
pdb_nodo pdb_make_node(pdb_nodo n, pdb_action a, pdb_state s);



/* FUNCION: pdb_free_nodo
 * DESC   : Funcion que libera un nodo
 * n      : Nodo a ser liberado
 * f      : Funcion para liberar el estado en el nodo
 */ 
void pdb_free_nodo(pdb_nodo n, void (*f)(void *a));


/* FUNCION: pdb_compare_nodo 
 * DESC   : Compara dos nodos
 * x      : Primer nodo a comparar
 * y      : Segundo nodo a comparar
 * RETORNA: Positivo si x > y, Cero si x = y, Negativo si x < y
 */
int pdb_compare_nodo(void *nx, void *ny);



#endif
