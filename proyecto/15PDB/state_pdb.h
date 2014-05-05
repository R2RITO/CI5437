#ifndef FILE_STATE_PDB
#define FILE_STATE_PDB

/* Arreglo con patrones de cuatro unos consecutivos */
int pdb_masks[8];

/* Arreglo con el complemento de cada patron del arreglo anterior*/
int pdb_cMasks[8];

/* Representacion de un estado de un 15-PUZZLE */
typedef struct _pdb_state {
    unsigned int quad_1; /* Representa el cuadrante superior */
    unsigned int quad_2; /* Representa el cuadrante inferior */
    unsigned short zero; /* Representa la posicion del cero  */
    unsigned short cost; /* Costo de llegar a partir del anterior, 0 o 1 */
} *pdb_state;

/* Arreglos de sucesores */
typedef struct _pdb_successors {
    pdb_state succ[4];
} *pdb_successors;

/* FUNCION: pdb_make_state
 * DESC   : Funcion para la creacion de un nuevo estado 
 * q1     : Representacion en entero de las primeras 8 casillas 
 * q2     : Representacion en entero de las ultimas 8 casillas
 * z      : Posicion actual del cero
 * RETORNA: Un nuevo esta con los valores q1 q2 y z
 */
pdb_state pdb_make_state(int q1, int q2, int z, int cost);

/* FUNCION: pdb_transition
 * DESC   : Funcion para calcular la transicion de un estado a otro
 * s      : Estado a partir del cual hacer transicion
 * a      : Accion a realizar: 'l', 'r', 'd', 'u' (En ingles)
 * RETORNA: Un nuevo estado resultado de aplicar el movimiento a en s\
 */
pdb_state pdb_transition(pdb_state s, char a);

/* FUNCION: pdb_get_succ
 * DESC   : Funcion que obtiene todos los sucesores de un estado
 * s      : Estado del cual extraer los sucesores
 * RETORNA: Un arreglo con los sucesores del estado s
 */
pdb_successors pdb_get_succ(pdb_state s);

/* FUNCION: pdb_print_state
 * DESC   : Imprime en pantalla la representacion de un estado
 * s      : Estado que se va a imprimir
 */
void pdb_print_state(pdb_state s);


/* FUNCION: pdb_free_state
 * DESC   : Libera el espacio reservado por un estado
 * sp     : Estado a ser liberado
 */
void pdb_free_state(void *sp);

/* FUNCION: pdb_init
 * DESC   : Funcion para la inicializacion y creacion del estado raiz
 * RETORNA: Un nuevo estado asociado a la configuracion inicial suministrada
 */
pdb_state pdb_init(char* input);

#endif
