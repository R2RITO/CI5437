#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "state.h"

typedef struct _pair {
    int x;
    int y;
} pair;

pair coords[16] = {
    {0,0},
    {0,1},
    {0,2},
    {0,3},
    {1,0},
    {1,1},
    {1,2},
    {1,3},
    {2,0},
    {2,1},
    {2,2},
    {2,3},
    {3,0},
    {3,1},
    {3,2},
    {3,3}
};

int manhattan(state s) {

    int save;
    int quad_1 = s->quad_1;
    int quad_2 = s->quad_2;
    int i;
    
    pair act;

    int res = 0;

    for (i=0; i<8; i++) {
        save = quad_1&(0xF0000000);
        save = save >> 28;
        save = save&(0x0000000F);
        quad_1 = quad_1 << 4;
        act = coords[save];
        res = res + abs(act.x - (i/4)) + abs(act.y - (i%4));
    }

    for (i=8; i<16; i++) {
        save = quad_2&(0xF0000000);
        save = save >> 28;
        save = save&(0x0000000F);
        quad_2 = quad_2 << 4;
        act = coords[save];
        res = res + abs(act.x - (i/4)) + abs(act.y - (i%4));
    }

    return res;
}


/*
Heap de Fibonacci
Representacion de estados para el 15puzzle
Representacion de los nodos de blai
Funcion init para el 15puzzle (pasar de enteros a bits)


Heuristica Manhattan para el 15puzzle
Heuristica PDB para 15 y 25 puzzle
Implementacion de A* e IDA*
Representacion de estados para el 25puzzle
Lista de nodos cerrados
*/
