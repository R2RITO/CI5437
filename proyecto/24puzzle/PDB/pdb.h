#ifndef FILE_PDB
#define FILE_PDB

#include "ucs.h"
#include "state_pdb.h"

int pdb(pdb_state s, hashval_z *t1, hashval_z *t2, hashval_z *t3);

void pdb_generate_pattern();

void pdb_erase_pattern();

#endif
