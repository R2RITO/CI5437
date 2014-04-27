#ifndef FILE_ASTAR
#define FILE_ASTAR

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "fiboheap.h"
#include "state.h"
#include "nodos.h"
#include "lista.h"
#include "caja.h"
#include "uthash.h"

#define INFINITO 51

/* Estructuras para la tabla de hash */

/* Estructura para la clave de la tabla*/
typedef struct {
  int q1;
  int q2;
} hashkey;

/* Estructura para los valores de la tabla */
typedef struct {
    hashkey key;
    int  closed;
    int  dist;   //distancia
    char accion; //accion que genero al estado
    int  g;      //costo
    UT_hash_handle hh;
} hashval;

/* FUNCION: astar
 * s      : Estado inicial s
 * DESC   : Implementacion del algoritmo A*
 * RETORNA: Una lista con el mejor camino del estado s al goal
 */
list astar(state initial_state);

#endif
