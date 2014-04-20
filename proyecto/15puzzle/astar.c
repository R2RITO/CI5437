#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "fiboheap.h"
#include "state.h"
#include "nodos.h"
#include "lista.h"
#include "caja.h"
#include "uthash.h"

#define INFINITO 51

/* Estructuras para la tabla de hash */

/* Estructura para la clave de la tabla*/
typedef struct {
  int q1;
  int q2;
} hashkey;

/* Estructura para los valores de la tabla */
typedef struct {
    hashkey key;
    int dist;
    UT_hash_handle hh;
} hashval;


/* FUNCION: astar
 * s      : Estado inicial s
 * DESC   : Implementacion del algoritmo A*
 * RETORNA: Una lista con el mejor camino del estado s al goal
 */
list astar() {

    /* Se crea la cola de prioridades */
    fiboheap q = make_fib_heap(compare_nodo, free_state); // LA FUNCION FREE_STATE NO SE LE DEBERIA PASAR, CAMBIAR ESTO
    /* Se inserta en el heap al estado inicial */
    fib_heap_insert(q,make_root_node(make_state(0x0197BD53, 0xEC4286AF, 0)));

    /* Se declaran variables para el conjunto de nodos cerrados */
    /* Closed es una tabla de hash donde estaran los nodos cerrados */
    /* Los otros dos valores son usados para buscar y agregar en la tabla */
    hashval look_up_key,*look_up,*closed = NULL;
    unsigned int keylen = sizeof(hashkey);
   
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
            if ((suc->succ[0]) && (manhattan(suc->succ[0]) < INFINITO)) {
                fib_heap_insert(q,make_node(n,'l',suc->succ[0]));
            }
            if ((suc->succ[1]) && (manhattan(suc->succ[1]) < INFINITO)) {
                fib_heap_insert(q,make_node(n,'r',suc->succ[1]));
            }
            if ((suc->succ[2]) && (manhattan(suc->succ[2]) < INFINITO)) {
                fib_heap_insert(q,make_node(n,'u',suc->succ[2]));
            }
            if ((suc->succ[3]) && (manhattan(suc->succ[3]) < INFINITO)) {
                fib_heap_insert(q,make_node(n,'d',suc->succ[3]));
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
