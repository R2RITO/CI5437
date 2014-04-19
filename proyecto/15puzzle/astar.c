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

#define INFINITO 51

/*
0 2 6 3
1 5 A 7
4 9 E B
8 C D F

*/

typedef struct {
  int q1 : 32;
  int q2 : 32;
} hashkey;

typedef struct {
    hashkey key;
    int dist;
    UT_hash_handle hh;
} hashval;

list astar() {
    fiboheap q = make_fib_heap(compare_nodo);
    fib_heap_insert(q,make_root_node(make_state(0x0197BD53, 0xEC4286AF, 0)));

    //fib_heap_insert(q,make_root_node(make_state(0x09236817, 0x4DFBCE5A, 0)));


    hashval look_up_key,*look_up,*closed = NULL;
    unsigned int keylen = sizeof(hashkey);
    
    int i = 0;   
 
    nodo n;
    successors suc;
    while (q->min) {
        n = fib_heap_extract_min(q);
        //memset(&look_up_key, 0, sizeof(hashval));
        look_up_key.key.q1 = (n->estado)->quad_1;
        look_up_key.key.q2 = (n->estado)->quad_2;
        /*state dummy = make_state(look_up_key.key.q1,look_up_key.key.q2,n->estado->zero);
        printf("look_up_key tiene:");
        print_state(dummy);*/

        HASH_FIND(hh,closed,&look_up_key.key,keylen,look_up);
/*        if (look_up) {
           printf("esta config ya estaba\n");
        } else {
           printf("look_up fue nulo\n");
        }       
  */      
/*        if (i%10000==0) {
            printf("Nodos explorados: %d\n",i);
        }
        i++;
*/
        if ((!look_up) || ((n->g) < (look_up->dist))) {
            //printf("entre\n");
            if (!look_up) {
                //printf("Cree uno nuevo\n");
                look_up = malloc(sizeof(hashval));
                //memset(look_up, 0, sizeof(hashval));
                look_up ->key.q1 = look_up_key.key.q1;
                look_up ->key.q2 = look_up_key.key.q2;
                HASH_ADD(hh, closed,key, keylen,look_up);
            }

            look_up->dist = (n->g);
            if (is_goal(n->estado)) {
                return extract_solution(n);
            }
            suc = get_succ(n->estado);
            if ((suc->succ[0]) && (manhattan(suc->succ[0]) < INFINITO)) {
                fib_heap_insert(q,make_node(n,'l',suc->succ[0]));
            }
            if ((suc->succ[1]) && (manhattan(suc->succ[1]) < INFINITO)) {
                fib_heap_insert(q,make_node(n,'r',suc->succ[1]));
            }
            if ((suc->succ[2]) && (manhattan(suc->succ[2]) < INFINITO)) {
                fib_heap_insert(q,make_node(n,'u',suc->succ[2]));
            }
            if ((suc->succ[3]) && (manhattan(suc->succ[3]) < INFINITO)) {
                fib_heap_insert(q,make_node(n,'d',suc->succ[3]));
            }
        }
    }
    return NULL;
}    
/*
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
}*/
