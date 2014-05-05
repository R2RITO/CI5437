#include "idastar.h"

char actions[4] = {'l','r','u','d'};
char cActions[4] = {'r','l','d','u'};

clock_t mts = 0;
clock_t mte = 0;

clock_t sts = 0;
clock_t ste = 0;

/*Variables globales que permiten simular un nodo a lo largo de la ejecucion*/
state current_state;
char  current_action;
int   current_g;

int numSucc = 0;

plan DFS_acotado(int t) {

    plan res;
    int hn = manhattan(current_state);

    if ((current_g)+hn > t) {
        res.sol = 0;
        res.tp  = current_g+hn;
        return res;
    }
    if (is_goal(current_state)){
        res.sol = 1; //hallado
        res.tp = current_g;
        return res;
    }

    int new_t = INFINITO;
    int i;

    /*para la presente llamada recursiva, se guardan los valores
     *del estado global*/
    char save_curr_action   = current_action;
    int  save_curr_g        = current_g;
    state save_curr_state   = current_state;

    for (i=0; i<4; i++) {
        //se genera el sucesor correspondiente a la accion denotada por i 
        state succ = transition(current_state,actions[i]);
        if (succ&&((!current_action)||(current_action!=cActions[i]))) {
            
            /*actualizacion del nodo simulado*/
            current_g = current_g + cost(current_state,current_action);
            current_action = actions[i];
            current_state = succ;
            numSucc++;            
            res = DFS_acotado(t);
            if (res.sol) {free(succ); return res;}
            if (res.tp < new_t) {new_t = res.tp;}
        }
        //libera al sucesor procesado
        free(succ);
        
        //se restauran el estado, la accion y el costo
        current_action = save_curr_action;
        current_g = save_curr_g;
        current_state = save_curr_state;
        
    }
    res.sol = 0;
    res.tp = new_t;
    return res;
}

void idastar(state initial_state) {

    current_state = make_state(initial_state->quad_1,initial_state->quad_2,initial_state->zero);
    current_action = 0;
    current_g = 0;

    numSucc = 1;

    int t = manhattan(current_state);
    plan actual;
    while (t < INFINITO) {
        actual = DFS_acotado(t);
        if (actual.sol) { printf("Final: %d Nodos: %d",current_g, numSucc); return; }
        t = actual.tp;
    }
    free_state(current_state);
    printf(" *No Encontre Solucion* ");
}
