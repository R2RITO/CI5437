/*#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stddef.h>

#include "fiboheap.h"
#include "state.h"
#include "nodos.h"
#include "lista.h"
#include "caja.h"
#include "uthash.h"

typedef struct _hashkey {
    int q1;
    int q2;
} hashkey;

typedef struct _hashval {
    UT_hash_handle hh;
    int dist;
    int q1;
    int q2;
} hashval;


main () {

    unsigned keylen;
    hashval *closed = NULL;
    hashval *look_up = NULL;
    hashkey *lookup_key = malloc(sizeof(struct _hashkey));

    keylen =   offsetof(hashval, q2)       /* offset of last key field */
   /*          + sizeof(int) - offsetof(hashval,q1);             /* size of last key field */
/*
    printf("Keylen : %u\n", keylen);

    lookup_key -> q1 = 1;
    lookup_key -> q2 = 2;

    HASH_FIND(hh, closed, &lookup_key->q1, 64, look_up );

    printf("Valor de look_up: %d\n", look_up);

    look_up = malloc(sizeof(struct _hashval));
    look_up -> dist = 0;
    look_up -> q1   = 1;
    look_up -> q2   = 2;
    HASH_ADD(hh, closed, q1, 64, look_up);  
    
    look_up = NULL;

    HASH_FIND(hh, closed, &lookup_key->q1, 64, look_up );

    printf("Valor de look_up: %d\n", look_up);

}*/
