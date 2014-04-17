#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "state.h"


/* Estructura para almacenar enteros en 32bits */
typedef struct _int32 {
    int val : 32;
} int32;

/* Arreglo con patrones de cinco unos consecutivos */
int32 masks[6];

/* Arreglo con el complemento de cada patron del arreglo anterior*/
int32 cMasks[6];

/* Metodo para inicializar el arreglo de mascaras */
void initializeMasks() {
    masks[0].val = 0xF8000000;
    masks[1].val = 0x07C00000;
    masks[2].val = 0x003E0000;
    masks[3].val = 0x0001F000;
    masks[4].val = 0x00000F80;
    masks[5].val = 0x0000007C;
}

/* Metodo para inicializar el arreglo de complementos */
void initializeCompMasks() {
    cMasks[0].val = 0x07FFFFFF;
    cMasks[1].val = 0xF83FFFFF;
    cMasks[2].val = 0xFFC1FFFF;
    cMasks[3].val = 0xFFFE0FFF;
    cMasks[4].val = 0xFFFFF07F;
    cMasks[5].val = 0xFFFFF083;
}



