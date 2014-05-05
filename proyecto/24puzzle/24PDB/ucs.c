#include "ucs.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdint.h>

void free_aux(void *a) {
    free(a);
}

/* compare_nodo_rep.val
 * Funcion que compara dos estados representados por enteros
 */
int compare_nodo_rep(void *nx, void *ny) {
    int64 *x = nx;
    int64 *y = ny;
    int64 p,q;
    p.val = ((*x).val >> 30) & (0x00000000FFFFFFFF);
    q.val = ((*y).val >> 30) & (0x00000000FFFFFFFF);

    return p.val-q.val;
}

/* 
 * posicionar
 * funcion que toma dos cuadrantes, una posicion y un valor e inserta en
 * el cuadrante correspondiente el valor en la posicion dada
 */
void posicionar(int64 *q1, int64 *q2, int pos, int value) {

    // Obtener el entero con el que voy a copiar
    
    int64 aux,m1,m2;
    unsigned long long val = value;

    if (pos == 24) {
        
        //Dividir a val en los 2 trozos.
        m1.val = (val >> 1) & (0x000000000000000F);
        m2.val = val & (0x0000000000000001);
        
    } else {
        aux.val = val << (((11 - (pos%12))*5)+4);
        aux.val = aux.val & pdb_masks[(pos%12)].val;
    }

    if (pos <= 11) {
        (*q1).val = (*q1).val | aux.val;
    } else if (pos <= 23) {
        (*q2).val = (*q2).val | aux.val;
    } else {
        (*q1).val = (*q1).val | m1.val;
        (*q2).val = (*q2).val | m2.val;
    }

    return;

}

/*
 * unrank
 * Funcion que toma un entero que representa un estado y retorna el estado
 * en cuestion
 */

pdb_state unrank(unsigned long long rep, int v1, int v2, int v3, int v4, int v5) {
    
    int64 q1;
    int64 q2;
    q1.val = 0;
    q2.val = 0;
    int zero = 0;
    int cost = 0;
    int pos;
    
    // Guardar la posicion del cero
    zero = rep & (0x000000000000001F);

    // Guardar el costo del estado
    cost = (rep >> 30) & (0x00000000FFFFFFFF);   
    
    // Posicionar el primer elemento 
    pos = (rep >> 5)&(0x000000000000001F);
    posicionar(&q1,&q2,pos,v1);
    
    // Posicionar el segundo elemento 
    pos = (rep >> 10)&(0x000000000000001F);
    posicionar(&q1,&q2,pos,v2);

    // Posicionar el tercer elemento 
    pos = (rep >> 15)&(0x000000000000001F);
    posicionar(&q1,&q2,pos,v3);

    // Posicionar el cuarto elemento 
    pos = (rep >> 20)&(0x000000000000001F);
    posicionar(&q1,&q2,pos,v4);

    if (v5 != -1) {
        // Posicionar el quinto elemento 
        pos = (rep >> 25)&(0x000000000000001F);
        posicionar(&q1,&q2,pos,v5);
    }



    return pdb_make_state(q1.val,q2.val,zero,cost);

}

unsigned long long rank(pdb_state s, int v1, int v2, int v3, int v4, int v5) {

    if (!s) return;
     
    int i,d;
    int64 rep,q1,q2,costo;
    rep.val = 0;
    q1.val = s -> quad_1;
    q2.val = s -> quad_2;
    d = 59; //11*5+4
    //pos va del 0 hasta el 25. si coincide con alguno de los vi valores
    //se coloca el valor de pos en la rep, en la posicion de bits adecuada

    int64 val,pos,aux;
    pos.val = 0;
    costo.val = s->cost;
    // Agregar la posicion del cero
    rep.val = rep.val | s -> zero;

    // Agregar el costo del estado
    rep.val = rep.val | (costo.val << 30);
    // Busqueda en el primer cuadrante

    for (i=0; i < 12; i++) {
        
        //se recoge el numero iesimo de la representacion, y se posiciona
        //al inicio de val.
        val.val = (((s->quad_1)&pdb_masks[i].val)>>d)&(0x00000000000000FF);
    
        if (val.val == v1) {
            aux.val = (pos.val << 5);
            rep.val = rep.val | aux.val;
        } else if (val.val == v2) {
            aux.val = (pos.val << 10);
            rep.val = rep.val | aux.val;
        } else if (val.val == v3) {
            aux.val = (pos.val << 15);
            rep.val = rep.val | aux.val;
        } else if (val.val == v4) {           
            aux.val = (pos.val << 20);
            rep.val = rep.val | aux.val;
        } else if ((val.val == v5) && (v5 != -1)) {
            aux.val = (pos.val << 25);
            rep.val = rep.val | aux.val;
        } 

        pos.val++;
        d = d - 5;

    }
    d = 59;
    
    // Busqueda en el segundo cuadrante

    for (i=0; i < 12; i++) {
        
        val.val = (((s->quad_2)&pdb_masks[i].val)>>d)&(0x00000000000000FF);
        if (val.val == v1) {
            aux.val = (pos.val << 5);
            rep.val = rep.val | aux.val;
        } else if (val.val == v2) {
            aux.val = (pos.val << 10);
            rep.val = rep.val | aux.val;
        } else if (val.val == v3) {
            aux.val = (pos.val << 15);
            rep.val = rep.val | aux.val;
        } else if (val.val == v4) {           
            aux.val = (pos.val << 20);
            rep.val = rep.val | aux.val;
        } else if ((val.val == v5) && (v5 != -1)) {
            aux.val = (pos.val << 25);
            rep.val = rep.val | aux.val;
        }

        pos.val++;
        d = d - 5;

    }
    
    /*se recupera el ultimo numero de la representacion 24-P */
    
    /*se recuperan los ultimos 4 bits del primer cuadrante*/
    int last_five_bits = ((s->quad_1)&(0x000000000000000F));
    /*se reserva espacio para el ultimo bit restante*/
    last_five_bits = last_five_bits << 1;
    /*se recupera el ultimo bit del segundo cuadrante*/
    int last_bit = ((s->quad_2)&(0x0000000000000001));
    last_five_bits = last_five_bits | last_bit;
    
    val.val = last_five_bits;
    if (val.val == v1) {
        aux.val = (pos.val << 5);
        rep.val = rep.val | aux.val;
    } else if (val.val == v2) {
        aux.val = (pos.val << 10);
        rep.val = rep.val | aux.val;
    } else if (val.val == v3) {
        aux.val = (pos.val << 15);
        rep.val = rep.val | aux.val;
    } else if (val.val == v4) {           
        aux.val = (pos.val << 20);
        rep.val = rep.val | aux.val;
    } else if ((val.val == v5) && (v5 != -1)) {
        aux.val = (pos.val << 25);
        rep.val = rep.val | aux.val;
    }

    return rep.val;

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
hashval_z *ucs(pdb_state initial_state, int v1, int v2, int v3, int v4, int v5) {
    

    /* Se crea la cola de prioridades */
    fiboheap q = make_fib_heap(compare_nodo_rep, free);
    /* Se inserta en el heap al estado inicial */
    int64 *rep_inicial = malloc(sizeof(int64));
    (*rep_inicial).val = rank(initial_state,v1,v2,v3,v4,v5);
    fib_heap_insert(q,rep_inicial);

    /* Se declaran variables para el conjunto de nodos cerrados */
    /* Closed es una tabla de hash donde estaran los nodos cerrados */
    /* Los otros dos valores son usados para buscar y agregar en la tabla */
    hashval look_up_key,*look_up,*closed = NULL;
    unsigned int keylen = sizeof(hashkey);

    hashval_z zLook_up_key, *zLook_up, *res = NULL;
    unsigned int zkeylen = sizeof(hashkey_z);
   
    /* Acciones */
    char accion[4] = {'l','r','u','d'};
    char cAccions[4] = {'r','l','d','u'};

    /* Para iterar en los sucesores */
    int i;

    long contador = 0;

    /* Variable auxiliar para extraer de la cola de prioridades */ 
    int64 *n;
    pdb_state s,sHijo;
    int64 *rep_hijo;

    /* Variable para almacenar los sucesores de un estado */
    pdb_successors suc;

    int agregados = 0;

    /* Mientras que el heap de fibonacci tenga un elemento */
    while (q->min) {
        
        /* Extraemos el minimo del heap de fibonacci */
        n = fib_heap_extract_min(q);
        s = unrank((*n).val,v1,v2,v3,v4,v5);
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
            
            zLook_up_key.key.q1 = look_up_key.key.q1;
            zLook_up_key.key.q2 = look_up_key.key.q2;
            HASH_FIND(hh,res,&zLook_up_key.key,zkeylen,zLook_up);
            
            if (zLook_up) {
                if (zLook_up -> dist > s -> cost) {
                    zLook_up -> dist = s -> cost;
                }
            } else {
                zLook_up = malloc(sizeof(hashval_z));
                zLook_up->key.q1 = look_up_key.key.q1;
                zLook_up->key.q2 = look_up_key.key.q2;
                zLook_up->dist = s->cost;
                HASH_ADD(hh,res,key,zkeylen,zLook_up);
                agregados++;
            }

            /* Obtener el costo del nuevo estado y guardarlo */
            look_up->dist = (s->cost);

            /* Obtenemos los sucesores del estado */
            suc = pdb_get_succ(s);

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
                        rep_hijo = malloc(sizeof(int64));                    
                        (*rep_hijo).val = rank(suc->succ[i],v1,v2,v3,v4,v5);
                        fib_heap_insert(q,rep_hijo);
                    }
                    //pdb_free_state(suc->succ[i]);
                }
            }
            //printf("************************************\n");            
            /* Liberamos el espacio usado para almacenar los sucesores */
            free(suc);
        }
        pdb_free_state(s);
    }
    printf("AGREGADOS: %d\n",agregados);
    /* Liberamos el espacio usado por la cola de prioridades */
    fib_heap_free(q);
    delete_all(closed);
    return res;
}

/*
void main() {

    int64 q1;
    int64 q2;
    q1.val = 0x00443214C74254BC;
    q2.val = 0x635CF84653A56D70;

    pdb_initializeMasks();
    pdb_initializeCompMasks();

    pdb_state s = pdb_make_state(q1.val,q2.val,0,0);

    pdb_print_state(s);

    long long rep = rank(s,21,22,23,24,-1);

    printf("Rep: %lld\n",rep);
    
    //rep = 0x000000010A418823;

    s = unrank(rep,21,22,23,24,-1);

    pdb_print_state(s);

    printf("Recuerda inicializar las mascaras\n");

    pdb_state estate = pdb_make_state(0x00443214C74254BC,0x635CF84653A56D70,0,5);
    pdb_print_state(estate);
    unsigned long long int ranki = rank(estate,1,2,3,4,24);    
    printf("mi long: %lu\n",ranki);

//00000  00101    00100   00011  00010 11001  000006
//11000 00100 00011 00010 00001   00000
//1 11000 00100 00011 00010 00001 00000
}
*/


