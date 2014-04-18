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

/*
0 2 6 3
1 5 A 7
4 9 E B
8 C D F

*/



list astar() {

    fiboheap q = make_fib_heap(compare_nodo);
    fib_heap_insert(q,make_root_node(make_state(0x41238567, 0xC9AB0DEF, 12)));

    nodo n;
    
    hashval *closed = NULL;
    hashval *look_up = NULL;
    hashkey *lookup_key = malloc(sizeof(struct _hashkey));

    successors suc;

    unsigned keylen = 64;
    

    while (q->min != NULL) {
        n = fib_heap_extract_min(q);
        
        lookup_key -> q1 = (n->estado)->quad_1;
        lookup_key -> q2 = (n->estado)->quad_2;

        HASH_FIND(hh, closed, &lookup_key->q1, 64, look_up );
        printf("Busque: %d ", look_up);

        if ((!look_up) || ((n->g) < (look_up->dist))) {

            if (!look_up) {
                printf("Cree uno nuevo\n");
                look_up = malloc(sizeof(struct _hashval));
                look_up -> q1 = lookup_key->q1;
                look_up -> q2 = lookup_key->q2;
                HASH_ADD(hh, closed, q1, keylen, look_up);
            } else {
                printf("Reabri un nodo\n");
            }

            look_up->dist = (n->g);
            if (is_goal(n->estado)) {
                print_state(n->estado);
                return extract_solution(n);
            }
            suc = get_succ(n->estado);
            if ((suc->succ[0]!=NULL) && (manhattan(suc->succ[0]) < 100)) {
                fib_heap_insert(q,make_node(n,'l',suc->succ[0]));
            }
            if ((suc->succ[1]!=NULL) && (manhattan(suc->succ[1]) < 100)) {
                fib_heap_insert(q,make_node(n,'r',suc->succ[1]));
            }
            if ((suc->succ[2]!=NULL) && (manhattan(suc->succ[2]) < 100)) {
                fib_heap_insert(q,make_node(n,'u',suc->succ[2]));
            }
            if ((suc->succ[3]!=NULL) && (manhattan(suc->succ[3]) < 100)) {
                fib_heap_insert(q,make_node(n,'d',suc->succ[3]));
            }
        }
    }
    return NULL;

}    


main () {

    initializeMasks();
    initializeCompMasks();

    list res = astar();
    int tam = res -> size;
    int i;

    printf("\nTam de la lista: %d\n", tam);
    
    box act = res -> first;
    for (i=0; i<tam; i++) {
        printf("%s ", getElemBox(act));
        act = getNextBox(act);
    }
    printf("\n");
}
