#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "state.h"

typedef struct _pair {
    int x;
    int y;
} pair;


/*

X X X X 
X X X X
X X X X
X X X X


*/

int coords[16][16] = {
    {0,1,2,3,1,2,3,4,2,3,4,5,3,4,5,6},
    {1,0,1,2,2,1,2,3,3,2,3,4,4,3,4,5},
    {2,1,0,2,3,2,1,2,4,3,2,3,5,4,3,4},
    {3,2,1,0,4,3,2,1,5,4,3,2,6,5,4,3},
    {1,2,3,4,0,1,2,3,1,2,3,4,2,3,4,5},
    {2,1,2,3,1,0,1,2,2,1,2,3,3,2,3,4},
    {3,2,1,2,2,1,0,1,3,2,1,2,4,3,2,3},
    {4,3,2,1,3,2,1,0,4,3,2,1,5,4,3,2},
    {2,3,4,5,1,2,3,4,0,1,2,3,1,2,3,4},
    {3,2,3,4,2,1,2,3,1,0,1,2,2,1,2,3},
    {4,3,2,3,3,2,1,2,2,1,0,1,3,2,1,2},
    {5,4,3,2,4,3,2,1,3,2,1,0,4,3,2,1},
    {3,4,5,6,2,3,4,5,1,2,3,4,0,1,2,3},
    {4,3,4,5,3,2,3,4,2,1,2,3,1,0,1,2},
    {5,4,3,4,4,3,2,3,3,2,1,2,2,1,0,1},
    {6,5,4,3,5,4,3,2,4,3,2,1,3,2,1,0}
};

int manhattan(state s) {

    int quad_1 = s->quad_1;
    int quad_2 = s->quad_2;
    int i;

    int res = 0;

    for (i=0; i<8; i++) {

        res = res + coords[((quad_1&(0xF0000000))>>28)&(0x0000000F)][i];
        quad_1 = quad_1 << 4;

        res = res + coords[((quad_2&(0xF0000000))>>28)&(0x0000000F)][i+8];
        quad_2 = quad_2 << 4;
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
