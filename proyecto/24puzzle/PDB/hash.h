#ifndef FILE_HASH
#define FILE_HASH
#include "uthash.h"
#include "nodos.h"

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
#endif
