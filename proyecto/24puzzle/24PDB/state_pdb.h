#ifndef FILE_STATE_PDB
#define FILE_STATE_PDB

/* Representacion de un estado de un 24-PUZZLE */
typedef struct _pdb_state {
    unsigned long long quad_1 : 64; /* Representa el primer cuadrante   */
    unsigned long long quad_2 : 64; /* Representa el segundo cuadrante  */
    unsigned int zero   :  5; /* Representa la posicion del cero  */
} *pdb_state;

/* Arreglos de sucesores */
typedef struct _pdb_successors {
    pdb_state succ[4];
} *pdb_successors;

/* FUNCION: make_state
 * DESC   : Funcion para la creacion de un nuevo estado 
 * q1     : Representacion en entero de las primeras 8 casillas 
 * q2     : Representacion en entero de las ultimas 8 casillas
 * z      : Posicion actual del cero
 * RETORNA: Un nuevo esta con los valores q1 q2 y z
 */
pdb_state pdb_make_state(long long q1, long long q2, int z);

/* FUNCION: is_goal
 * DESC   : Verifica si el estado s es un estado final
 * s      : Es el estado que se va a verificar
 * RETORNA: Devuelve 1 si es goal. 0 En caso contrario
 */
int pdb_is_goal(pdb_state s);

/* FUNCION: transition
 * DESC   : Funcion para calcular la transicion de un estado a otro
 * s      : Estado a partir del cual hacer transicion
 * a      : Accion a realizar: 'l', 'r', 'd', 'u' (En ingles)
 * RETORNA: Un nuevo estado resultado de aplicar el movimiento a en s\
 */
pdb_state pdb_transition(pdb_state s, char a);

/* FUNCION: get_succ
 * DESC   : Funcion que obtiene todos los sucesores de un estado
 * s      : Estado del cual extraer los sucesores
 * RETORNA: Un arreglo con los sucesores del estado s
 */
pdb_successors pdb_get_succ(pdb_state s);

/* FUNCION: init
 * DESC   : Funcion para la inicializacion y creacion del estado raiz
 * RETORNA: Un nuevo estado asociado a la configuracion inicial suministrada
 */
pdb_state pdb_init(char* input);

/* FUNCION: print_state
 * DESC   : Imprime en pantalla la representacion de un estado
 * s      : Estado que se va a imprimir
 */
void pdb_print_state(pdb_state s);

#endif
