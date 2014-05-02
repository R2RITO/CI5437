#include "ucs.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdint.h>

void free_aux(void *a) {
    nodo n = (nodo) a;
    free_nodo(a, free_state);
}

/* FUNCION: astar
 * s      : Estado inicial s
 * DESC   : Implementacion del algoritmo A*
 * RETORNA: Una lista con el mejor camino del estado s al goal
 */
list ucs(state initial_state) {

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

    printf("Comenzo ucs\n");
    print_state(initial_state);    
    printf("JJ\n");

    /* Mientras que el heap de fibonacci tenga un elemento */
    while (q->min) {
        
        /* Extraemos el minimo del heap de fibonacci */
        n = fib_heap_extract_min(q);

        printf("Extract\n");
        print_state(n->estado);
        printf("Costo\n");
	printf("%d\n",n->g);

        /* Buscamos en la tabla de hash dicho estado */
        look_up_key.key.q1 = (n->estado)->quad_1;
        look_up_key.key.q2 = (n->estado)->quad_2;
        HASH_FIND(hh,closed,&look_up_key.key,keylen,look_up);

        /* Si no lo encuentra o si su distancia es mayor (Reabrirlo) */
        if (!look_up) {

            /* Debemos agregarlo a la tabla de hash */
            look_up = malloc(sizeof(hashval));
            look_up ->key.q1 = look_up_key.key.q1;
            look_up ->key.q2 = look_up_key.key.q2;
            HASH_ADD(hh, closed,key, keylen,look_up);
            

            /* Obtener el costo del nuevo estado y guardarlo */
            look_up->dist = (n->g);

            /* Obtenemos los sucesores del estado */
            suc = get_succ(n->estado);

            printf("Sucesores\n");

            /* Agregamos los sucesores del estado n a la cola de prioridades */
            for (i=0; i<4; i++) {
                
                if (suc->succ[i]) {
                    if (((!n->a)||(n->a!=cAccions[i]))) {
                        print_state(suc->succ[i]);
                        printf("\n");
                        fib_heap_insert(q,make_node(n,accion[i],suc->succ[i]));
                    }
                }
            }
            
            /* Liberamos el espacio usado para almacenar los sucesores */
            free(suc);
        }
        //free_nodo(n,free_state);
    }

    printf("Sali del guail\n");

    /* Liberamos el espacio usado por la cola de prioridades */
    //fib_heap_free(q);
    // Falta liberar HASH
    return NULL;
}   


int rank1(state s, int v1, int v2, int v3, int v4, int v5) {

    if (s == NULL) return;

    int i,pos,val,aux;
    int rep = 0;
    int q1 = s -> quad_1;
    int q2 = s -> quad_2;
    int d = 28;

    pos = 0;

    // Agregar la posicion del cero
    rep = rep | s -> zero;

    // Busqueda en el primer cuadrante

    for (i=0; i < 8; i++) {
        
        val = (((s->quad_1)&masks[i])>>d)&(0x0000000F);

        switch (val) {

            case v1:
                aux = (pos << 4) & masks[6];
                rep = rep | aux;
                break; 
            case v2:
                aux = (pos << 8) & masks[5];
                rep = rep | aux;
                break; 
            case v3:
                aux = (pos << 12) & masks[4];
                rep = rep | aux;
                break;            
            case v4:
                aux = (pos << 16) & masks[3];
                rep = rep | aux;
                break;
            case v5:
                aux = (pos << 20) & masks[2];
                rep = rep | aux;
                break;

        }

        pos++;
        d = d - 4;

    }

    d = 28;
    
    // Busqueda en el segundo cuadrante

    for (i=0; i < 8; i++) {
        
        val = (((s->quad_2)&masks[i])>>d)&(0x0000000F);

        switch (val) {

            case 1:
                aux = (pos << 4) & masks[6];
                rep = rep | aux;
                break; 
            case 2:
                aux = (pos << 8) & masks[5];
                rep = rep | aux;
                break; 
            case 3:
                aux = (pos << 12) & masks[4];
                rep = rep | aux;
                break;            
            case 4:
                aux = (pos << 16) & masks[3];
                rep = rep | aux;
                break;
            case 5:
                aux = (pos << 20) & masks[2];
                rep = rep | aux;
                break;

        }

        pos++;
        d = d - 4;

    }

    return rep;

}

void main() {

    int q1 = 0x61234560;
    int q2 = 0x66666666;

    initializeMasks();
    initializeCompMasks();

    state s = make_state(q1,q2,7,0);
    print_state(s);
    //list lst = ucs(s);

    int h = rank1(s,1,2,3,4,5);

    printf("\n%d\n",h);  


}



