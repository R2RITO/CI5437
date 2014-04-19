#ifndef FILE_HASH
#define FILE_HASH
#include "uthash.h"
#include "state.h"

typedef struct {
  int q1;
  int q2;
} hashkey;

typedef struct {
    hashkey key;
    int dist;
    state s;
    UT_hash_handle hh;
} hashval;
#endif
