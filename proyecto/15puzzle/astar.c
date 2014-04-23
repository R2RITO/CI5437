#include "astar.h"

void free_aux(void *a) {
    nodo n = (nodo) a;
    free_nodo(a, free_state);
}

/* FUNCION: astar
 * s      : Estado inicial s
 * DESC   : Implementacion del algoritmo A*
 * RETORNA: Una lista con el mejor camino del estado s al goal
 */
list astar(state initial_state) {

    /* Se crea la cola de prioridades */
    fiboheap q = make_fib_heap(compare_nodo, free_aux);
    /* Se inserta en el heap al estado inicial */
    fib_heap_insert(q,make_root_node(initial_state));

    /* Se declaran variables para el conjunto de nodos cerrados */
    /* Closed es una tabla de hash donde estaran los nodos cerrados */
    /* Los otros dos valores son usados para buscar y agregar en la tabla */
    hashval look_up_key,*look_up,*closed = NULL;
    unsigned int keylen = sizeof(hashkey);
   
    /* Acciones */
    char accion[4] = {'l','r','u','d'};
    char cAccions[4] = {'r','l','d','u'};

    /* Para iterar en los sucesores */
    int i;

    /* Variable auxiliar para extraer de la cola de prioridades */ 
    nodo n;

    /* Variable para almacenar los sucesores de un estado */
    successors suc;

    /* Mientras que el heap de fibonacci tenga un elemento */
    while (q->min) {
        
        /* Extraemos el minimo del heap de fibonacci */
        n = fib_heap_extract_min(q);

        /* Buscamos en la tabla de hash dicho estado */
        look_up_key.key.q1 = (n->estado)->quad_1;
        look_up_key.key.q2 = (n->estado)->quad_2;
        HASH_FIND(hh,closed,&look_up_key.key,keylen,look_up);

        /* Si no lo encuentra o si su distancia es mayor (Reabrirlo) */
        if ((!look_up) || ((n->g) < (look_up->dist))) {

            /* Si no lo encontro, debemos agregarlo a la tabla de hash */
            if (!look_up) {
                look_up = malloc(sizeof(hashval));
                look_up ->key.q1 = look_up_key.key.q1;
                look_up ->key.q2 = look_up_key.key.q2;
                HASH_ADD(hh, closed,key, keylen,look_up);
            }

            /* Se actualiza la distancia en la tabla de hash */
            look_up->dist = (n->g);

            /* Si es el estado objetivo, retornamos la solucion */
            if (is_goal(n->estado)) {
            
                list res = extract_solution(n);

                //free_nodo(n, free_state);

                /* Liberamos el espacio usado por la cola de prioridades */
                fib_heap_free(q);

                //Falta liberar HASH
                return res;
            }

            /* Obtenemos los sucesores del estado */
            suc = get_succ(n->estado);

            /* Agregamos los sucesores del estado n a la cola de prioridades */
            for (i=0; i<4; i++) {
                if ((suc->succ[i]) && (manhattan(suc->succ[i]) < INFINITO)) {
                    if (((!n->a)||(n->a!=cAccions[i]))) {
                        fib_heap_insert(q,make_node(n,accion[i],suc->succ[i]));
                    }
                }
            }
            
            /* Liberamos el espacio usado para almacenar los sucesores */
            free(suc);
        }
        //free_nodo(n,free_state);
    }
    /* Liberamos el espacio usado por la cola de prioridades */
    fib_heap_free(q);
    // Falta liberar HASH
    return NULL;
}   
