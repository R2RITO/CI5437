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
#include "uthash.h"

#define INFINITO 100

typedef struct {
    int sol;
    int size_res;
    int tp;
} plan;

typedef struct {
  int q1;
  int q2;
} hashkey;

typedef struct {
    hashkey key;
    int dist;
    nodo n;
    UT_hash_handle hh;
} hashval;

plan DFS_acotado(int t);

list idastar(state initial_state);

#endif
