#include "astar.h"

void free_aux(void *a) {
    nodo n = (nodo) a;
    free_nodo(a, free_state);
}
/* Se declaran variables para el conjunto de nodos cerrados */
/* Closed es una tabla de hash donde estaran los nodos cerrados */
/* Los otros dos valores son usados para buscar y agregar en la tabla */
hashval look_up_key,*look_up,*closed = NULL;
unsigned int keylen = sizeof(hashkey);

/* Funcion para destruir la tabla de hash */
void delete_all() {
  hashval *c_val, *tmp;

  HASH_ITER(hh, closed, c_val, tmp) {
    HASH_DEL(closed,c_val);
    free(c_val);
  }
}

/* FUNCION: compare_state
* DESC : Compara dos nodos
* nx : Primero nodo a comparar
* ny : Segundo nodo a comparar
* RETORNA: Negativo si nx < ny, Cero si nx = ny, Positivo si nx > ny
*/
int compare_state(void *sx, void *sy) {

    state x = (state) sx;
    state y = (state) sy;
    
    /* Buscamos en la tabla de hash la informacion asociada al estado sx */
    look_up_key.key.q1 = x->quad_1;
    look_up_key.key.q2 = x->quad_2;
    HASH_FIND(hh,closed,&look_up_key.key,keylen,look_up);
    int gx = look_up->g;
    
    /* Buscamos en la tabla de hash la informacion asociada al estado sy */
    look_up_key.key.q1 = y->quad_1;
    look_up_key.key.q2 = y->quad_2;
    HASH_FIND(hh,closed,&look_up_key.key,keylen,look_up);
    int gy = look_up->g;
    
    int res = (gx + manhattan(x)) - (gy + manhattan(y));
    if (res) {
        return res;
    //caso de empate, el criterio aplica en base a los cosgtos individuales
    } else {
        return (gx-gy);
    }
}


/* FUNCION: astar
* s : Estado inicial s
* DESC : Implementacion del algoritmo A*
* RETORNA: Una lista con el mejor camino del estado s al goal
*/
list astar(state initial_state) {
    
    /* Se crea la cola de prioridades */
    fiboheap q = make_fib_heap(compare_state, free_state);
    /* Se inserta en el heap al estado inicial */

    look_up = malloc(sizeof(hashval));
    look_up ->key.q1 = initial_state->quad_1;
    look_up ->key.q2 = initial_state->quad_2;
    look_up ->accion = 0;
    look_up ->g = 0;
    look_up ->closed = 0;
    HASH_ADD(hh, closed,key, keylen,look_up);
    
    fib_heap_insert(q,initial_state);
   
    /* Acciones */
    char accion[4] = {'l','r','u','d'};
    char cAccions[4] = {'r','l','d','u'};
    char a_parent;

    /* Para iterar en los sucesores */
    int i, g_parent;

    /* Variable auxiliar para extraer de la cola de prioridades */
    state s;

    /* Variable para almacenar los sucesores de un estado */
    successors suc;

    /* Mientras que el heap de fibonacci tenga un elemento */
    while (q->min) {  

        /* Extraemos el minimo del heap de fibonacci */
        s = (state) fib_heap_extract_min(q);

        /* Buscamos en la tabla de hash dicho estado */
        look_up_key.key.q1 = s->quad_1;
        look_up_key.key.q2 = s->quad_2;
        HASH_FIND(hh,closed,&look_up_key.key,keylen,look_up);

        /* Si no lo encuentra o si su distancia es mayor (Reabrirlo) */
        if (!look_up->closed) {

            look_up->closed = 1;
           /* Si no lo encontro, debemos agregarlo a la tabla de hash */

            /* Se actualiza la distancia en la tabla de hash */
            g_parent = look_up->g;
            a_parent = look_up->accion;
            /* Si es el estado objetivo, retornamos la solucion */
            if (is_goal(s)) {
            
                //int res = look_up->g;
                printf("Final: %d ",look_up->g);
                list res = NULL ;//extract_solution(n);
                //free_nodo(n, free_state);
                /* Liberamos el espacio usado por la cola de prioridades */
                fib_heap_free(q);
                delete_all();
                closed = NULL;
                look_up = NULL;
                return res;
            }

            /* Obtenemos los sucesores del estado */
            suc = get_succ(s);
             
            /* Agregamos los sucesores del estado n a la cola de prioridades */
            
            for (i=0; i<4; i++) {
                if ((suc->succ[i]) && (manhattan(suc->succ[i]) < INFINITO)) {
                    if (((!a_parent)||(a_parent!=cAccions[i]))) {

                        /* Buscamos en la tabla de hash dicho estado */
                        look_up_key.key.q1 = suc->succ[i]->quad_1;
                        look_up_key.key.q2 = suc->succ[i]->quad_2;
                        HASH_FIND(hh,closed,&look_up_key.key,keylen,look_up);
                        
                        if (!look_up) {
                        look_up = malloc(sizeof(hashval));
                        look_up ->key.q1 = suc->succ[i]->quad_1;
                        look_up ->key.q2 = suc->succ[i]->quad_2;
                        look_up ->accion = accion[i];
                        look_up ->g = g_parent + 1;
                        look_up ->closed = 0;
                        HASH_ADD(hh, closed,key, keylen,look_up);
                                          
                        fib_heap_insert(q,suc->succ[i]);
                        } else {
                            free_state(suc->succ[i]);
                        }
                    } else if (a_parent==cAccions[i]){
                        free_state(suc->succ[i]); 
                    }
                }
            }
            /* Liberamos el espacio usado para almacenar los sucesores */
            free(suc);
            free_state(s);
        }
    }
    /* Liberamos el espacio usado por la cola de prioridades */
    fib_heap_free(q);
    delete_all();
    closed = NULL;
    look_up = NULL;
    return NULL;
} 
