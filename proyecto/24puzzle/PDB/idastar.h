#ifndef FILE_IDASTAR
#define FILE_IDASTAR
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
#include "ucs.h"
#include "uthash.h"

#define INFINITO_IDASTAR 100

typedef struct {
    int sol;
    int tp;
} plan;

plan DFS_acotado(int t);

void idastar(state initial_state);

#endif
