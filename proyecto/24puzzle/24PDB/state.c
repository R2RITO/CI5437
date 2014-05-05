#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include "state.h"

/* Arreglo con patrones de cuatro unos consecutivos */
int masks[8];

/* Arreglo con el complemento de cada patron del arreglo anterior*/
int cMasks[8];

/* Metodo para inicializar el arreglo de mascaras */
void initializeMasks() {
    masks[0] = 0xF0000000;
    masks[1] = 0x0F000000;
    masks[2] = 0x00F00000;
    masks[3] = 0x000F0000;
    masks[4] = 0x0000F000;
    masks[5] = 0x00000F00;
    masks[6] = 0x000000F0;
    masks[7] = 0x0000000F;
}

/* Metodo para inicializar el arreglo de complementos */
void initializeCompMasks() {
    cMasks[0] = 0x0FFFFFFF;
    cMasks[1] = 0xF0FFFFFF;
    cMasks[2] = 0xFF0FFFFF;
    cMasks[3] = 0xFFF0FFFF;
    cMasks[4] = 0xFFFF0FFF;
    cMasks[5] = 0xFFFFF0FF;
    cMasks[6] = 0xFFFFFF0F;
    cMasks[7] = 0xFFFFFFF0;
}

/* FUNCION: make_state
 * DESC   : Funcion para la creacion de un nuevo estado 
 * q1     : Representacion en entero de las primeras 8 casillas 
 * q2     : Representacion en entero de las ultimas 8 casillas
 * z      : Posicion actual del cero
 * RETORNA: Un nuevo esta con los valores q1 q2 y z
 */
state make_state(int q1, int q2, int z) {
    state newState = malloc(sizeof(struct _state));
    newState -> quad_1 = q1;
    newState -> quad_2 = q2;
    newState -> zero   = z;
    return newState;
}

/* FUNCION: is_goal
 * DESC   : Verifica si el estado s es un estado final
 * s      : Es el estado que se va a verificar
 * RETORNA: Devuelve 1 si es goal. 0 En caso contrario
 */
int is_goal(state s) {
    int q1;
    int q2;
    q1 = 0x01234567;
    q2 = 0x89ABCDEF;
    return (q1==s->quad_1)&&(q2==s->quad_2);
}

/* FUNCION: moveLR
 * DESC   : Devuelve un estado resultado de mover el cero a la izquierda
 *          o a la derecha. El estado s no es alterado
 * s      : Estado a partir del cual se va a mover
 * d      : Desplazamiento hacia la izquierda o derecha del estado s
 * RETORNA: Un nuevo estado resultado de aplicar el desplazamiento d en s
 */
state moveLR(state s, int d) {
    
    int save;
    int newq;
    int zero = s->zero;
    state nState = NULL;
    save = 0;
    newq = 0;

    if (zero < 8) {
        // Si estamos en el primer cuadrante
        save = (s->quad_1)&masks[zero+d];
        if ( d < 0 ) {
            // Si el movimiento es a la izquierda
            save = save >> 4;
            save = save&(0x0FFFFFFF);
        } else {
            // Si el movimiento es a la derecha
            save = save << 4;
        }
        newq = (s->quad_1)&cMasks[zero+d];
        newq = newq | save;
        nState = make_state(newq,s->quad_2, zero+d);
    } else {
        // Si estamos en el segundo cuadrante
        save = (s->quad_2)&masks[(zero+d)%8];
        if ( d < 0 ) {
            // Si el movimiento es a la izquierda
            save = save >> 4;
            save = save&(0x0FFFFFFF);
        } else {
            // Si el movimiento es a la derecha
            save = save << 4;
        }
        newq = (s->quad_2)&cMasks[(zero+d)%8];
        newq = newq | save;
        nState = make_state(s->quad_1, newq, zero+d);
    }                    
    return nState;
}

/* FUNCION: moveUD
 * DESC   : Desplazamientos hacia arriba o abajo desde un estado s
 * s      : Estado a partir del cual hacer el desplazamiento
 * d      : Desplazamiento hacia arriba o hacia abajo a realizar
 * RETORNA: Un nuevo estado resultado de aplicar el desplazamiento d desde s
 */
state moveUD(state s, int d) {

    int save;
    int newq1;
    int newq2;
    int zero = s->zero;
    state nState = NULL;
    save = 0;
    newq1 = 0;
    newq2 = 0;

    int caso = zero/4;
    
    switch (caso) {
        case 0:
            // Estamos en la primera linea del puzzle
            save = (s->quad_1)&masks[zero+d];
            save = save << 16;
            newq1 = (s->quad_1)&cMasks[zero+d];
            newq1 = newq1 | save;
            nState = make_state(newq1,s->quad_2,zero+d);
            break;
        case 1:
            // Estamos en la segunda linea del puzzle
            if ( d < 0 ) {
                // Si el movimiento es arriba
                save = (s->quad_1)&masks[(zero+d)%8];
                save = save >> 16;
                save = save&(0x0000FFFF);
                newq1 = (s->quad_1)&cMasks[(zero+d)%8];
                newq1 = newq1 | save;
                nState = make_state(newq1, s->quad_2, zero+d);
            } else {
                // Si el movimiento es hacia abajo
                save = (s->quad_2)&masks[(zero+d)%8];
                save = save >> 16;
                save = save&(0x0000FFFF);
                newq1 = (s->quad_1) | save;
                newq2 = (s->quad_2)&cMasks[(zero+d)%8];
                nState = make_state(newq1,newq2,zero+d);
            }
            break;
        case 2:
            // Estamos en la tercera linea del puzzle
            if ( d < 0 ) {
                // Si el movimiento es hacia arriba
                save = (s->quad_1)&masks[(zero+d)%8];
                save = save << 16;
                newq1 = (s->quad_1)&cMasks[(zero+d)%8];
                newq2 = (s->quad_2) | save;
                nState = make_state(newq1,newq2,zero+d);
            } else {
                // Si el movimiento es hacia abajo
                save = (s->quad_2)&masks[(zero+d)%8];
                save = save << 16;
                newq2 = (s->quad_2)&cMasks[(zero+d)%8];
                newq2 = newq2 | save;
                nState = make_state(s->quad_1,newq2,zero+d);
            }
            break;
        case 3:
            // Estamos en la cuarta linea del puzzle
            save = (s->quad_2)&masks[(zero+d)%8];
            save = save >> 16;
            save = save&(0x0000FFFF);
            newq1 = (s->quad_2)&cMasks[(zero+d)%8];
            newq1 = newq1 | save;
            nState = make_state(s->quad_1,newq1,zero+d);
            break;
    }
}

/* FUNCION: transition
 * DESC   : Funcion para calcular la transicion de un estado a otro
 * s      : Estado a partir del cual hacer transicion
 * a      : Accion a realizar: 'l', 'r', 'd', 'u' (En ingles)
 * RETORNA: Un nuevo estado resultado de aplicar el movimiento a en s\
 */
state transition(state s, char a) {
    
    int save;
    int newq;
    int zero = s->zero;
    state nState = NULL;
    save = 0;
    newq = 0;

    // Siempre estamos moviendo el cero
    switch (a) {
        case 'l':
                // Movimiento hacia la izquierda
                if (zero%4 != 0) {
                    nState = moveLR(s,-1);
                }
                break;
        case 'r':
                // Movimiento hacia la derecha
                if ((zero+1)%4 != 0) {
                    nState = moveLR(s,1);
                }
                break;
        case 'd':
                // Movimiento hacia abajo
                if (zero+4 < 16) {
                    nState = moveUD(s,4);
                }
                break;
        case 'u':
                // Movimiento hacia arriba
                if (zero-4 >= 0) {
                    nState = moveUD(s,-4);
                }
                break;
    }
    return nState;
}

/* FUNCION: init
 * DESC   : Funcion para la inicializacion y creacion del estado raiz
 * RETORNA: Un nuevo estado asociado a la configuracion inicial suministrada
 */
state init(char* input){
    /*Inicializacion de las mascaras usadas para computar la representacion
     * de la cuadricula*/
    initializeMasks();
    initializeCompMasks();
    printf("%s",input);
    
    int k[16];
    sscanf(input," %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d \n",
                   &k[0],&k[1],&k[2],&k[3],&k[4],&k[5],&k[6],&k[7],
                   &k[8],&k[9],&k[10],&k[11],&k[12],&k[13],&k[14],&k[15]);            
    
    int quad_index;
    int quad_1 = 0; /*almacenamiento de la primera mitad de la cuadricula*/
    int quad_2 = 0; /*almacenamiento de la segunda mitad de la cuadricula*/
    int pos_zero = 0; /*posicion del 0 en la cuadricula*/
    for (quad_index=0; quad_index < 8; quad_index++){
       int quad_2_index = quad_index+8;
       
       /*se recuerda la posicion del 0 en la cuadricula*/
       if (k[quad_index]==0) {
            pos_zero = quad_index;
       }
       if (k[quad_2_index]==0) {
            pos_zero = quad_2_index;
       }
       /*desplazamiento de los digitos significados, permiten alojar el nuevo
        *numero entrante de 4 bits*/
       quad_1 = quad_1 << 4;
       quad_2 = quad_2 << 4;
       
       /*se conservan los bits encendidos de la cuadricula, agregando
        *la representacion binaria del numero entrante en los ultimos 4 bits*/
       quad_1 = quad_1 | k[quad_index];
       quad_2 = quad_2 | k[quad_2_index];
    }
   
    return make_state(quad_1,quad_2,pos_zero);
}

/* FUNCION: get_succ
 * DESC   : Funcion que obtiene todos los sucesores de un estado
 * s      : Estado del cual extraer los sucesores
 * RETORNA: Un arreglo con los sucesores del estado s
 */
successors get_succ(state s) {
    successors res = malloc(sizeof(struct _successors));
    res->succ[0] = transition(s,'l');
    res->succ[1] = transition(s,'r');
    res->succ[2] = transition(s,'u');
    res->succ[3] = transition(s,'d');
    return res;
}

/* FUNCION: print_state
 * DESC   : Imprime en pantalla la representacion de un estado
 * s      : Estado que se va a imprimir
 */
void print_state(state s) {
    // Si el estado es null, retornar
    if (s==NULL) return;
    
    int i;
    // Declaramos un d entero para hacer los shift necesarios
    int d = 28;

    // Imprimimos el primer cuadrante
    for (i=0; i<8; i++) {
        // Salto de linea cada vez que se termina de imprimir una linea
        if (i%4 == 0) {
            printf("\n");
        }
        // Imprimimos el valor haciendo los shift correspondientes
        printf("%2d  ", ((s->quad_1)&masks[i])>>d);
        // Se decrementa la cantidad de bits a mover en la siguiente iteracion
        d = d-4;
    }
    // Reinicializamos el numero de bits a mover
    d = 28;
    
    // Imprimimos el segundo cuadrante
    for (i=0; i<8; i++) {
        // Salto de linea cada vez que se termina de imprimir una linea
        if (i%4 == 0) {
            printf("\n");
        }
        // Imprimimos el valor haciendo los shift correspondientes
        printf("%2d  ", ((s->quad_2)&masks[i])>>d);
        // Se decrementa la cantidad de bits a mover en la siguiente iteracion
        d = d-4;
    }
    printf("\n");
}

/* FUNCION: free_state
 * DESC   : Libera el espacio reservado por un estado
 * s      : Estado a ser liberado
 */
void free_state(void *sp) {
    state s = (state) sp;
    free(s);
}
