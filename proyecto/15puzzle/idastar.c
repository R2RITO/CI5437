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
            look_up_key.key.q1 = (s->succ[i])->quad_1;
            look_up_key.key.q2 = (s->succ[i])->quad_2;
            HASH_FIND(hh,IDAHash,&look_up_key.key,keylen,look_up);
            if (look_up) {
                m = look_up -> n;
                m -> parent = n;
                m -> a = actions[i];
                free_state(s->succ[i]);
                // el costo del nodo cambia?? 
            } else {
                m = make_node(n,actions[i],s->succ[i]);
                look_up = malloc(sizeof(hashval));
                look_up ->key.q1 = look_up_key.key.q1;
                look_up ->key.q2 = look_up_key.key.q2;
                look_up -> n = m;
                HASH_ADD(hh, IDAHash,key, keylen,look_up);
            }

            res = DFS_acotado(m,t);
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
    nodo n  = make_root_node(make_state(0x0197BD53, 0xEC4286AF, 0));

    // 001 : 53 0.65 EXPLOTO DURISIMO
    // nodo n = make_root_node(make_state(0x7F82D63C, 0xB04A951E, 9));
    
    look_up = malloc(sizeof(hashval));
    look_up -> key.q1 = look_up_key.key.q1;
    look_up -> key.q2 = look_up_key.key.q2;
    look_up -> n = n;
    HASH_ADD(hh, IDAHash, key, keylen, look_up);
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
