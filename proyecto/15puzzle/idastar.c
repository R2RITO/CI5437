#include "idastar.h"

char actions[4] = {'l','r','u','d'};
char cActions[4] = {'r','l','d','u'};
hashval look_up_key,*look_up,*IDAHash = NULL;
unsigned int keylen = sizeof(hashkey);

clock_t mts = 0;
clock_t mte = 0;

clock_t sts = 0;
clock_t ste = 0;

plan DFS_acotado(nodo n, int t) {
    nodo m;
    plan res;
    int hn = 0;

    hn = manhattan(n->estado);


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

    successors s = get_succ(n->estado);

    for (i=0; i<4; i++) {
        if (s->succ[i]&&((!n->a)||(n->a!=cActions[i]))) {
            m = make_node(n,actions[i],s->succ[i]);
            res = DFS_acotado(m,t);
            if (res.sol) { return res; }
            if (res.tp < new_t) { new_t = res.tp; }
        }
    }
    res.sol = NULL;
    res.tp = new_t;
    return res;
}

list idastar(state initial_state) {

    nodo n  = make_root_node(initial_state);

    int t = manhattan(n->estado);
    plan actual;
    while (t < INFINITO) {
        actual = DFS_acotado(n,t);
        if (actual.sol) { return actual.sol; }
        t = actual.tp;
    }
    return NULL;
}
