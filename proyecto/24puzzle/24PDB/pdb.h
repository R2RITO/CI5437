#ifndef FILE_PDB
#define FILE_PDB

#include "ucs.h"
#include "state_pdb.h"

int pdb(pdb_state s, hashval *t1, hashval *t2, hashval *t3, hashval *t4, hashval *t5);

void pdb_generate_pattern();

void pdb_erase_pattern();

#endif
