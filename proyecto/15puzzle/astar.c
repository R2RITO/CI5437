#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "fiboheap.h"
#include "state.h"
#include "nodos.h"
#include "lista.h"
#include "caja.h"

/*
0 2 6 3
1 5 A 7
4 9 E B
8 C D F

*/

list astar() {

    fiboheap q = make_fib_heap(compare_nodo);
    fib_heap_insert(q,make_root_node(make_state(0x026315A7, 0x49EB8CDF, 0)));

    nodo n;

    successors suc;

    while (q->min != NULL) {
        n = fib_heap_extract_min(q);
        if (((n->estado)->closed != 1) || ((n->g) < ((n->estado)->dist))) {

            (n->estado)->closed = 1;
            (n->estado)->dist = (n->g);

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
