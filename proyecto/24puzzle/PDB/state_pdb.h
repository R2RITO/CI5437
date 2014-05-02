#ifndef FILE_STATE_PDB
#define FILE_STATE_PDB

/* Arreglo con patrones de cuatro unos consecutivos */
int masks[8];

/* Arreglo con el complemento de cada patron del arreglo anterior*/
int cMasks[8];

/* Representacion de un estado de un 15-PUZZLE */
typedef struct _state {
    unsigned int quad_1; /* Representa el cuadrante superior */
    unsigned int quad_2; /* Representa el cuadrante inferior */
    unsigned short zero; /* Representa la posicion del cero  */
    unsigned short cost; /* Costo de llegar a partir del anterior, 0 o 1 */
} *state;

/* Arreglos de sucesores */
typedef struct _successors {
    state succ[4];
} *successors;

/* FUNCION: make_state
 * DESC   : Funcion para la creacion de un nuevo estado 
 * q1     : Representacion en entero de las primeras 8 casillas 
 * q2     : Representacion en entero de las ultimas 8 casillas
 * z      : Posicion actual del cero
 * RETORNA: Un nuevo esta con los valores q1 q2 y z
 */
state make_state(int q1, int q2, int z, int cost);

/* FUNCION: transition
 * DESC   : Funcion para calcular la transicion de un estado a otro
 * s      : Estado a partir del cual hacer transicion
 * a      : Accion a realizar: 'l', 'r', 'd', 'u' (En ingles)
 * RETORNA: Un nuevo estado resultado de aplicar el movimiento a en s\
 */
state transition(state s, char a);

/* FUNCION: get_succ
 * DESC   : Funcion que obtiene todos los sucesores de un estado
 * s      : Estado del cual extraer los sucesores
 * RETORNA: Un arreglo con los sucesores del estado s
 */
successors get_succ(state s);

/* FUNCION: print_state
 * DESC   : Imprime en pantalla la representacion de un estado
 * s      : Estado que se va a imprimir
 */
void print_state(state s);


/* FUNCION: free_state
 * DESC   : Libera el espacio reservado por un estado
 * sp     : Estado a ser liberado
 */
void free_state(void *sp);

/* FUNCION: init
 * DESC   : Funcion para la inicializacion y creacion del estado raiz
 * RETORNA: Un nuevo estado asociado a la configuracion inicial suministrada
 */
state init(char* input);

#endif
