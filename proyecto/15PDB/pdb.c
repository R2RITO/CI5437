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

    int res_q1 = 0;
    int res_q2 = 0;
    int save;
    int copy;
    int i;

    save = s->quad_1;

    for (i=0; i<8; i++) {
        copy = save&(0x0000000F);
        if (copy==a) {
           res_q1 = res_q1 | (a << i*4);
        } else if (copy==b) {
            res_q1 = res_q1 | (b << i*4);
        } else if (copy==c) {
            res_q1 = res_q1 | (c << i*4);
        } else if (copy==d) {
            res_q1 = res_q1 | (d << i*4);
        } else if (copy==e) {
            res_q1 = res_q1 | (e << i*4);
        }
        save = save >> 4;
    }
    
    save = s->quad_2;

    for (i=0; i<8; i++) {
        copy = save&(0x0000000F);
        if (copy==a) {
            res_q2 = res_q2 | (a << i*4);
        } else if (copy==b) {
            res_q2 = res_q2 | (b << i*4);
        } else if (copy==c) {
            res_q2 = res_q2 | (c << i*4);
        } else if (copy==d) {
            res_q2 = res_q2 | (d << i*4);
        } else if (copy==e) {
            res_q2 = res_q2 | (e << i*4);
        }
        save = save >> 4;
    }

    pdb_state res = pdb_make_state(res_q1, res_q2, s->zero, 0);
    return res;

}

int pdb(pdb_state s, hashval_z *t1, hashval_z *t2, hashval_z *t3) {

    int res = 0;

    hashval_z look_up_key,*look_up = NULL;
    unsigned int keylen = sizeof(hashkey_z); 
//1 2 4 5 8, 3 6 7 A B, 9 12 13 14 15
    pdb_state s1 = dividir(s,1,2,4,5,8);
    pdb_state s2 = dividir(s,3,6,7,10,11);
    pdb_state s3 = dividir(s,9,12,13,14,15);

    look_up_key.key.q1 = s1->quad_1;
    look_up_key.key.q2 = s1->quad_2;
    HASH_FIND(hh,t1,&look_up_key.key,keylen,look_up);

    res += look_up -> dist;

    look_up_key.key.q1 = s2->quad_1;
    look_up_key.key.q2 = s2->quad_2;
    HASH_FIND(hh,t2,&look_up_key.key,keylen,look_up);

    res += look_up -> dist;

    look_up_key.key.q1 = s3->quad_1;
    look_up_key.key.q2 = s3->quad_2;
    HASH_FIND(hh,t3,&look_up_key.key,keylen,look_up);

    res += look_up -> dist;

    return res;
}
//1 2 4 5 8, 3 6 7 A B, 9 12 13 14 15
void pdb_generate_pattern(){
    pdb_initializeMasks();
    pdb_initializeCompMasks();
    printf("Generando base de datos de patrones PDB... (0/3)\n");
    pdb_state goal_state = pdb_make_state(0x01234567,0x89ABCDEF,0,0);
    ucs(goal_state,1,2,4,5,8,"12458.txt");
    ucs(goal_state,3,6,7,10,11,"367AB.txt");
    ucs(goal_state,9,12,13,14,15,"9CDEF.txt"); 
    t1 = generar("12458.txt");
    printf("Fase 1 completada... (1/3)\n");
    t2 = generar("367AB.txt");
    printf("Fase 2 completada... (2/3)\n");
    t3 = generar("9CDEF.txt");
    printf("Fase 3 completada. Patrones generados (3/3)\n");
}

void pdb_erase_pattern(){
    delete_all_z(t1);
    delete_all_z(t2);
    delete_all_z(t3);
}
