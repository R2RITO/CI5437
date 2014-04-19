#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>

#include "fiboheap.h"
#include "state.h"
#include "nodos.h"
#include "lista.h"
#include "caja.h"
#include "hash.h"

#define INFINITO 100

typedef struct {
    list sol;
    int tp;
} plan;

char actions[4] = {'l','r','u','d'};
char cActions[4] = {'r','l','d','u'};

clock_t mts = 0;
clock_t mte = 0;

clock_t sts = 0;
clock_t ste = 0;

plan DFS_acotado(nodo n, int t) {
    plan res;
    int hn = 0;

    //mts = clock();
    hn = manhattan(n->estado);
    //mte = mte + (clock()-mts);

    if ((n->g)+hn > t) {
        res.sol = NULL;
        res.tp  = (n->g)+hn;
        return res;
    }
    if (is_goal(n->estado)) {
        res.sol = extract_solution(n); 
        res.tp  = (n->g);
        return res;
    }

    int new_t = INFINITO;
    int i;
    //sts = clock();
    successors s = get_succ(n->estado);
    //ste = ste + (clock()-sts);
    for (i=0; i<4; i++) {
        if (s->succ[i]&&((!n->a)||(n->a!=cActions[i]))) {
            res = DFS_acotado(make_node(n,actions[i],s->succ[i]),t);
            if (res.sol) { return res; }
            if (res.tp < new_t) { new_t = res.tp; }
        }
    }
    res.sol = NULL;
    res.tp = new_t;
    return res;
}

list idastar() {
    // 079 : 0 1 9 7 11 13 5 3 14 12 4 2 8 6 10 15 : 28 30 32 34 36 38 40 42 441778 42 0.01 44177800
    nodo n = make_root_node(make_state(0x0197BD53, 0xEC4286AF, 0));
    // 001 : 53 0.65 EXPLOTO DURISIMO
    //nodo n = make_root_node(make_state(0x7F82D63C, 0xB04A951E, 9));
    // 005 : 56 5.24 
    //nodo n = make_root_node(make_state(0x5CA7FBE0, 0x821D3496, 7));

    int t = manhattan(n->estado);
    plan actual;
    while (t < INFINITO) {
        actual = DFS_acotado(n,t);
        if (actual.sol) { return actual.sol; }
        t = actual.tp;
    }
    return NULL;
}



main () {

    initializeMasks();
    initializeCompMasks();

    printf("EMPIEZO IDA*!!\n");
    clock_t start = clock(); 
    list res = idastar();
    clock_t end = clock();
    printf("TERMINO IDA*!!\n");

    printf("EMPIEZO A* \n");
    clock_t start2 = clock();
    list res2 = (list) astar();
    clock_t end2 = clock();
    printf("TERMINO A*\n");

    int tam = res -> size;
    int i;

    box act;

    printf("IDA* se tardo: %f\n", (float)(end-start)/CLOCKS_PER_SEC);
    printf("Tiempo invertido en manhattan: %f\n", (float)mte/CLOCKS_PER_SEC);
    printf("Tiempo invertido sacando sucesores: %f\n", (float)ste/CLOCKS_PER_SEC);
    printf("A* se tardo: %f\n", (float)(end2-start2)/CLOCKS_PER_SEC);
    printf("\nTam de la lista: %d %d\n", tam, res2->size);
  
    printf("Lista 1: "); 
    act = res -> first;
    for (i=0; i<tam; i++) {
        printf("%s ", getElemBox(act));
        act = getNextBox(act);
    }
    printf("\n");

    printf("Lista 2: ");
    act = res2 -> first;
    for (i=0; i<res2->size; i++) {
        printf("%s ", getElemBox(act));
        act = getNextBox(act);
    }
    printf("\n");
}
