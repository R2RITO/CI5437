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
    printf("costo:%lu, mi rep es:%lu\n",s->cost,rep.val);
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
        } else if (val.val == v5) {
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
        } else if (val.val == v5) {
            aux.val = (pos.val << 25);
            rep.val = rep.val | aux.val;
        }

        pos.val++;
        d = d - 5;

    }
  
                printf("mi res es: %lu\n",rep.val);
    
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
    } else if (val.val == v5) {
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

    /*pdb_state estate = pdb_make_state(0x00443214C74254BC,0x635CF84653A56D70,0,5);
    pdb_print_state(estate);
    unsigned long long int ranki = rank(estate,1,2,3,4,24);    
    printf("mi long: %lu\n",ranki);
*/
//00000  00101    00100   00011  00010 11001  000006
//11000 00100 00011 00010 00001   00000
//1 11000 00100 00011 00010 00001 00000
}



