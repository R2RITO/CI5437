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

state dividir(state s, int a, int b, int c, int d, int e) {

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

    state res = make_state(res_q1, res_q2, s->zero, 0);
    return res;

}

int pdb(state s, hashval *t1, hashval *t2, hashval *t3) {

    int res = 0;

    hashval look_up_key,*look_up = NULL;
    unsigned int keylen = sizeof(hashkey); 

    state s1 = dividir(s,1,2,3,4,5);
    state s2 = dividir(s,6,7,8,9,10);
    state s3 = dividir(s,11,12,13,14,15);

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

    return res;
}
