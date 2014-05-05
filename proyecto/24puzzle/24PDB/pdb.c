#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdint.h>

#include "pdb.h"
#include "uthash.h"

/*

    0! D  A  3
    4  F  6  7
    8  9  2  B
    C  1  E  5

    0! 0  0  3
    4  0  0  0
    0  0  2  0
    0  1  0  5

*/

pdb_state dividir(pdb_state s, int a, int b, int c, int d, int e) {

    int64 res_q1;
    res_q1.val = 0;
    int64 res_q2;
    res_q2.val = 0;
    int64 save;
    int64 copy;
    copy.val = 0;
    int i;

    save.val = s->quad_1;
    save.val = (save.val >> 4) & (0x0FFFFFFFFFFFFFFF);

    for (i=0; i<12; i++) {
        copy.val = save.val&(0x000000000000001F);
        if (copy.val==a) {
            res_q1.val = res_q1.val | (a << ((i*5)+4));
        } else if (copy.val==b) {
            res_q1.val = res_q1.val | (b << ((i*5)+4));
        } else if (copy.val==c) {
            res_q1.val = res_q1.val | (c << ((i*5)+4));
        } else if (copy.val==d) {
            res_q1.val = res_q1.val | (d << ((i*5)+4));
        } else if (copy.val==e) {
            res_q1.val = res_q1.val | (e << ((i*5)+4));
        }
        save.val = save.val >> 5;
    }
    
    save.val = s->quad_2;

    for (i=0; i<12; i++) {
        copy.val = save.val&(0x000000000000001F);
        if (copy.val==a) {
            res_q2.val = res_q2.val | (a << ((i*5)+4));
        } else if (copy.val==b) {
            res_q2.val = res_q2.val | (b << ((i*5)+4));
        } else if (copy.val==c) {
            res_q2.val = res_q2.val | (c << ((i*5)+4));
        } else if (copy.val==d) {
            res_q2.val = res_q2.val | (d << ((i*5)+4));
        } else if (copy.val==e) {
            res_q2.val = res_q2.val | (e << ((i*5)+4));
        }
        save.val = save.val >> 5;
    }


    /*se recupera el ultimo numero de la representacion 24-P */

    /*se recuperan los ultimos 4 bits del primer cuadrante*/
    long long last_four_bits = ((s->quad_1)&(0x000000000000000F));
    long long last_five_bits;
    /*se reserva espacio para el ultimo bit restante*/
    last_five_bits = last_four_bits << 1;
    /*se recupera el ultimo bit del segundo cuadrante*/
    long long last_bit = ((s->quad_2)&(0x0000000000000001));
    last_five_bits = last_five_bits | last_bit;

    copy.val = last_five_bits;

    if (copy.val==a) {
        res_q1.val = res_q1.val | last_four_bits;
        res_q2.val = res_q2.val | last_bit;
    } else if (copy.val==b) {
        res_q1.val = res_q1.val | last_four_bits;
        res_q2.val = res_q2.val | last_bit;
    } else if (copy.val==c) {
        res_q1.val = res_q1.val | last_four_bits;
        res_q2.val = res_q2.val | last_bit;
    } else if (copy.val==d) {
        res_q1.val = res_q1.val | last_four_bits;
        res_q2.val = res_q2.val | last_bit;
    } else if (copy.val==e) {
        res_q1.val = res_q1.val | last_four_bits;
        res_q2.val = res_q2.val | last_bit;
    }

    pdb_state res = pdb_make_state(res_q1.val, res_q2.val, s->zero, 0);
    return res;

}

int pdb(pdb_state s, hashval *t1, hashval *t2, hashval *t3, hashval *t4, hashval *t5) {

    int res = 0;

    hashval look_up_key,*look_up = NULL;
    unsigned int keylen = sizeof(hashkey); 
//1 2 4 5 8, 3 6 7 A B, 9 12 13 14 15
    pdb_state s1 = dividir(s,1,2,5,6,7);
    pdb_state s2 = dividir(s,3,4,8,9,13);
    pdb_state s3 = dividir(s,10,11,15,16,20);
    pdb_state s4 = dividir(s,12,17,21,22,-1);
    pdb_state s5 = dividir(s,14,18,19,23,24);

    look_up_key.key.q1 = s1->quad_1;
    look_up_key.key.q2 = s1->quad_2;
    look_up_key.key.zero = s1->zero;
    HASH_FIND(hh,t1,&look_up_key.key,keylen,look_up);

    res += look_up -> dist;

    look_up_key.key.q1 = s2->quad_1;
    look_up_key.key.q2 = s2->quad_2;
    look_up_key.key.zero = s2->zero;
    HASH_FIND(hh,t2,&look_up_key.key,keylen,look_up);

    res += look_up -> dist;

    look_up_key.key.q1 = s3->quad_1;
    look_up_key.key.q2 = s3->quad_2;
    look_up_key.key.zero = s3->zero;
    HASH_FIND(hh,t3,&look_up_key.key,keylen,look_up);

    res += look_up -> dist;

    look_up_key.key.q1 = s4->quad_1;
    look_up_key.key.q2 = s4->quad_2;
    look_up_key.key.zero = s4->zero;
    HASH_FIND(hh,t4,&look_up_key.key,keylen,look_up);

    res += look_up -> dist;

    look_up_key.key.q1 = s5->quad_1;
    look_up_key.key.q2 = s5->quad_2;
    look_up_key.key.zero = s5->zero;
    HASH_FIND(hh,t5,&look_up_key.key,keylen,look_up);

    res += look_up -> dist;

    return res;
}
//1 2 4 5 8, 3 6 7 A B, 9 12 13 14 15
void pdb_generate_pattern(){
    pdb_initializeMasks();
    pdb_initializeCompMasks();
    printf("Generando base de datos de patrones PDB... (0/5)\n");
    pdb_state goal_state = pdb_make_state(0x00443214C74254BC,0x635CF84653A56D70,0,0);   
    t1 = ucs(goal_state,1,2,5,6,7);
    printf("Fase 1 completada... (1/5)\n");
    t2 = ucs(goal_state,3,4,8,9,13);
    printf("Fase 2 completada... (2/5)\n");
    t3 = ucs(goal_state,10,11,15,16,20);
    printf("Fase 3 completada... (3/5)\n");
    t4 = ucs(goal_state,12,17,21,22,-1);
    printf("Fase 4 completada... (4/5)\n");
    t5 = ucs(goal_state,14,18,19,23,24);
    printf("Fase 5 completada. Patrones generados (5/5)\n");

}

void pdb_erase_pattern(){
    delete_all(t1);
    delete_all(t2);
    delete_all(t3);
    delete_all(t4);
    delete_all(t5);
}
