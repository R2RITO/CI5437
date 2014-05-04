#include "ucs.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdint.h>

void free_aux(void *a) {
    free(a);
}

/* compare_nodo_rep
 * Funcion que compara dos estados representados por enteros
 */
int compare_nodo_rep(void *nx, void *ny) {
    int *x = nx;
    int *y = ny;
    int p,q;
    p = (*x >> 24) & (0x000000FF);
    q = (*y >> 24) & (0x000000FF);

    return p-q;
}

int rank(state s, int v1, int v2, int v3, int v4, int v5) {

    if (s == NULL) return;

    int i,pos,val,aux;
    int rep = 0;
    int q1 = s -> quad_1;
    int q2 = s -> quad_2;
    int d = 28;

    pos = 0;

    // Agregar la posicion del cero
    rep = rep | s -> zero;

    // Agregar el costo del estado
    rep = rep | (((s -> cost) << 24)&(0xFF000000));

    // Busqueda en el primer cuadrante

    for (i=0; i < 8; i++) {
        
        val = (((s->quad_1)&masks[i])>>d)&(0x0000000F);

        if (val == v1) {
            aux = (pos << 4) & masks[6];
            rep = rep | aux;
        } else if (val == v2) {
            aux = (pos << 8) & masks[5];
            rep = rep | aux;
        } else if (val == v3) {
            aux = (pos << 12) & masks[4];
            rep = rep | aux;
        } else if (val == v4) {           
            aux = (pos << 16) & masks[3];
            rep = rep | aux;
        } else if (val == v5) {
            aux = (pos << 20) & masks[2];
            rep = rep | aux;
        }

        pos++;
        d = d - 4;

    }
    d = 28;
    
    // Busqueda en el segundo cuadrante

    for (i=0; i < 8; i++) {
        
        val = (((s->quad_2)&masks[i])>>d)&(0x0000000F);

        if (val == v1) {
            aux = (pos << 4) & masks[6];
            rep = rep | aux;
        } else if (val == v2) {
            aux = (pos << 8) & masks[5];
            rep = rep | aux;
        } else if (val == v3) {
            aux = (pos << 12) & masks[4];
            rep = rep | aux;
        } else if (val == v4) {           
            aux = (pos << 16) & masks[3];
            rep = rep | aux;
        } else if (val == v5) {
            aux = (pos << 20) & masks[2];
            rep = rep | aux;
        }


        pos++;
        d = d - 4;

    }

    return rep;

}

/* 
 * posicionar
 * funcion que toma dos cuadrantes, una posicion y un valor e inserta en
 * el cuadrante correspondiente el valor en la posicion dada
 */
void posicionar(int *q1, int *q2, int pos, int val) {

    // Obtener el entero con el que voy a copiar
    int aux = val << ((7 - (pos%8))*4);
    aux = aux & masks[(pos%8)];

    if (pos <= 7) {
        *q1 = *q1 | aux;
    } else {
        *q2 = *q2 | aux;
    }

    return;

}

/*
 * unrank
 * Funcion que toma un entero que representa un estado y retorna el estado
 * en cuestion
 */

state unrank(int rep, int v1, int v2, int v3, int v4, int v5) {
    
    int q1 = 0;
    int q2 = 0;
    int zero = 0;
    int cost = 0;
    int pos;
    
    // Guardar la posicion del cero
    zero = rep & masks[7];

    // Guardar el costo del estado
    cost = (rep >> 24) & (0x000000FF);
        
    // Posicionar el primer elemento 
    pos = (rep >> 4)&(0x0000000F);
    posicionar(&q1,&q2,pos,v1);
    
    // Posicionar el segundo elemento 
    pos = (rep >> 8)&(0x0000000F);
    posicionar(&q1,&q2,pos,v2);

    // Posicionar el tercer elemento 
    pos = (rep >> 12)&(0x0000000F);
    posicionar(&q1,&q2,pos,v3);

    // Posicionar el cuarto elemento 
    pos = (rep >> 16)&(0x0000000F);
    posicionar(&q1,&q2,pos,v4);

    // Posicionar el quinto elemento 
    pos = (rep >> 20)&(0x0000000F);
    posicionar(&q1,&q2,pos,v5);

    return make_state(q1,q2,zero,cost);

}

/* Funcion para destruir la tabla de hash */

void delete_all(hashval *tabla) {
  hashval *c_val, *tmp = NULL;
  HASH_ITER(hh, tabla, c_val, tmp) {
    HASH_DEL(tabla,c_val);
    free(c_val);
  }
}


/* FUNCION: ucs
 * s      : Estado inicial s
 * DESC   : Implementacion del algoritmo UCS para PDB
 * RETORNA: Una tabla de hash con los estados posibles (con la PDB)
 */
hashval *ucs(state initial_state, int v1, int v2, int v3, int v4, int v5) {

    /* Se crea la cola de prioridades */
    fiboheap q = make_fib_heap(compare_nodo_rep, free);
    /* Se inserta en el heap al estado inicial */
    int *rep_inicial = malloc(sizeof(int));
    *rep_inicial = rank(initial_state,v1,v2,v3,v4,v5);
    fib_heap_insert(q,rep_inicial);

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

    long contador = 0;

    /* Variable auxiliar para extraer de la cola de prioridades */ 
    int *n;
    state s,sHijo;
    int *rep_hijo;

    /* Variable para almacenar los sucesores de un estado */
    successors suc;

    /* Mientras que el heap de fibonacci tenga un elemento */
    while (q->min) {
        
        /* Extraemos el minimo del heap de fibonacci */
        n = fib_heap_extract_min(q);
        s = unrank(*n,v1,v2,v3,v4,v5);
        free(n);
        //printf("************ EXTRAIGO *************\n");            
        //print_state(s);
        //printf("***********************************\n"); 

        /* Buscamos en la tabla de hash dicho estado */
        look_up_key.key.q1 = s->quad_1;
        look_up_key.key.q2 = s->quad_2;
        look_up_key.key.zero = s->zero;
        HASH_FIND(hh,closed,&look_up_key.key,keylen,look_up);

        /* Si no lo encuentra o si su distancia es mayor (Reabrirlo) */
        if (!look_up) {

            contador++;
            /* Debemos agregarlo a la tabla de hash */
            look_up = malloc(sizeof(hashval));
            look_up->key.q1   = look_up_key.key.q1;
            look_up->key.q2   = look_up_key.key.q2;
            look_up->key.zero = look_up_key.key.zero;
            HASH_ADD(hh, closed,key, keylen,look_up);
            

            /* Obtener el costo del nuevo estado y guardarlo */
            look_up->dist = (s->cost);

            /* Obtenemos los sucesores del estado */
            suc = get_succ(s);

            /* Agregamos los sucesores del estado n a la cola de prioridades */
            //printf("************ SUCESORES *************\n");
            for (i=0; i<4; i++) {
                
                if (suc->succ[i]) {
                    //print_state(suc->succ[i]);

                    look_up_key.key.q1 = suc->succ[i]->quad_1;
                    look_up_key.key.q2 = suc->succ[i]->quad_2;
                    look_up_key.key.zero = suc->succ[i]->zero;
                    HASH_FIND(hh,closed,&look_up_key.key,keylen,look_up);

                    if (!look_up) {                    
                        rep_hijo = malloc(sizeof(int));                    
                        *rep_hijo = rank(suc->succ[i],v1,v2,v3,v4,v5);
                        fib_heap_insert(q,rep_hijo);
                    }
                    free_state(suc->succ[i]);
                }
            }
            //printf("************************************\n");            
            /* Liberamos el espacio usado para almacenar los sucesores */
            free(suc);
        }
        free_state(s);
    }

    printf("Sali del guail y agregue a hash %ld nodos\n",contador);

    /* Liberamos el espacio usado por la cola de prioridades */
    fib_heap_free(q);
    // Falta liberar HASH
    return closed;
}   

void main() {

    int q1 = 0x01234567;
    int q2 = 0x89ABCDEF;

    initializeMasks();
    initializeCompMasks();

    state s = make_state(q1,q2,0,0);
    print_state(s);
    printf("Empece el primero\n");
    ucs(s,1,2,3,4,5);
    printf("Empece el segundo\n");
    ucs(s,6,7,8,9,10);
    printf("Empece el tercero\n");
    ucs(s,11,12,13,14,15);

    /*int h = rank(s,11,12,13,14,15);

    printf("\n%d\n",h);  

    state p = unrank(h,11,12,13,14,15);

    print_state(p);
    printf("\n Costo: %d, Zero: %d\n",p->cost,p->zero);

    printf("Comparacion: %d\n",compare_nodo_rep(&h,&h));*/
    
}



