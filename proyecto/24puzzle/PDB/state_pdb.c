#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include "state_pdb.h"
//#include "manhattan.h"

/* Metodo para inicializar el arreglo de mascaras */
void pdb_initializeMasks() {
    pdb_masks[0] = 0xF0000000;
    pdb_masks[1] = 0x0F000000;
    pdb_masks[2] = 0x00F00000;
    pdb_masks[3] = 0x000F0000;
    pdb_masks[4] = 0x0000F000;
    pdb_masks[5] = 0x00000F00;
    pdb_masks[6] = 0x000000F0;
    pdb_masks[7] = 0x0000000F;
}

/* Metodo para inicializar el arreglo de complementos */
void pdb_initializeCompMasks() {
    pdb_cMasks[0] = 0x0FFFFFFF;
    pdb_cMasks[1] = 0xF0FFFFFF;
    pdb_cMasks[2] = 0xFF0FFFFF;
    pdb_cMasks[3] = 0xFFF0FFFF;
    pdb_cMasks[4] = 0xFFFF0FFF;
    pdb_cMasks[5] = 0xFFFFF0FF;
    pdb_cMasks[6] = 0xFFFFFF0F;
    pdb_cMasks[7] = 0xFFFFFFF0;
}

/* FUNCION: pdb_make_state
 * DESC   : Funcion para la creacion de un nuevo estado 
 * q1     : Representacion en entero de las primeras 8 casillas 
 * q2     : Representacion en entero de las ultimas 8 casillas
 * z      : Posicion actual del cero
 * RETORNA: Un nuevo esta con los valores q1 q2 y z
 */
pdb_state pdb_make_state(int q1, int q2, int z, int cost) {
    pdb_state newState = malloc(sizeof(struct _pdb_state));
    newState -> quad_1 = q1;
    newState -> quad_2 = q2;
    newState -> zero   = z;
    newState -> cost   = cost;
    return newState;
}

/* FUNCION: pdb_moveLR
 * DESC   : Devuelve un estado resultado de mover el cero a la izquierda
 *          o a la derecha. El estado s no es alterado
 * s      : Estado a partir del cual se va a mover
 * d      : Desplazamiento hacia la izquierda o derecha del estado s
 * RETORNA: Un nuevo estado resultado de aplicar el desplazamiento d en s
 */
pdb_state pdb_moveLR(pdb_state s, int d) {
    
    int save;
    int newq;
    int zero = s->zero;
    pdb_state nState = NULL;
    save = 0;
    newq = 0;
    int cost;

    if (zero < 8) {
        // Si estamos en el primer cuadrante
        save = (s->quad_1)&pdb_masks[zero+d];

        // Guardar el valor de la casilla destino para costo
        cost = save && 1;


        if ( d < 0 ) {
            // Si el movimiento es a la izquierda
            save = save >> 4;
            save = save&(0x0FFFFFFF);
        } else {
            // Si el movimiento es a la derecha
            save = save << 4;
        }
        newq = (s->quad_1)&pdb_cMasks[zero+d];
        newq = newq | save;
        nState = pdb_make_state(newq,s->quad_2, zero+d, cost + s->cost);
    } else {
        // Si estamos en el segundo cuadrante
        save = (s->quad_2)&pdb_masks[(zero+d)%8];

        // Guardar el valor de la casilla destino para costo
        cost = save && 1;

        if ( d < 0 ) {
            // Si el movimiento es a la izquierda
            save = save >> 4;
            save = save&(0x0FFFFFFF);
        } else {
            // Si el movimiento es a la derecha
            save = save << 4;
        }
        newq = (s->quad_2)&pdb_cMasks[(zero+d)%8];
        newq = newq | save;
        nState = pdb_make_state(s->quad_1, newq, zero+d, cost + s->cost);
    }                    
    return nState;
}

/* FUNCION: pdb_moveUD
 * DESC   : Desplazamientos hacia arriba o abajo desde un estado s
 * s      : Estado a partir del cual hacer el desplazamiento
 * d      : Desplazamiento hacia arriba o hacia abajo a realizar
 * RETORNA: Un nuevo estado resultado de aplicar el desplazamiento d desde s
 */
pdb_state pdb_moveUD(pdb_state s, int d) {

    int save;
    int newq1;
    int newq2;
    int zero = s->zero;
    pdb_state nState = NULL;
    save = 0;
    newq1 = 0;
    newq2 = 0;
    int cost;

    int caso = zero/4;
    
    switch (caso) {
        case 0:
            // Estamos en la primera linea del puzzle
            save = (s->quad_1)&pdb_masks[zero+d];

            // Guardar el valor de la casilla destino para costo
            cost = save && 1;            

            save = save << 16;
            newq1 = (s->quad_1)&pdb_cMasks[zero+d];
            newq1 = newq1 | save;
            nState = pdb_make_state(newq1,s->quad_2,zero+d, cost + s->cost);
            break;
        case 1:
            // Estamos en la segunda linea del puzzle
            if ( d < 0 ) {
                // Si el movimiento es arriba
                save = (s->quad_1)&pdb_masks[(zero+d)%8];

                // Guardar el valor de la casilla destino para costo
                cost = save && 1;

                save = save >> 16;
                save = save&(0x0000FFFF);
                newq1 = (s->quad_1)&pdb_cMasks[(zero+d)%8];
                newq1 = newq1 | save;
                nState = pdb_make_state(newq1, s->quad_2, zero+d, cost + s->cost);
            } else {
                // Si el movimiento es hacia abajo
                save = (s->quad_2)&pdb_masks[(zero+d)%8];

                // Guardar el valor de la casilla destino para costo
                cost = save && 1;

                save = save >> 16;
                save = save&(0x0000FFFF);
                newq1 = (s->quad_1) | save;
                newq2 = (s->quad_2)&pdb_cMasks[(zero+d)%8];
                nState = pdb_make_state(newq1,newq2,zero+d, cost + s->cost);
            }
            break;
        case 2:
            // Estamos en la tercera linea del puzzle
            if ( d < 0 ) {
                // Si el movimiento es hacia arriba
                save = (s->quad_1)&pdb_masks[(zero+d)%8];

                // Guardar el valor de la casilla destino para costo
                cost = save && 1;

                save = save << 16;
                newq1 = (s->quad_1)&pdb_cMasks[(zero+d)%8];
                newq2 = (s->quad_2) | save;
                nState = pdb_make_state(newq1,newq2,zero+d, cost + s->cost);
            } else {
                // Si el movimiento es hacia abajo
                save = (s->quad_2)&pdb_masks[(zero+d)%8];

                // Guardar el valor de la casilla destino para costo
                cost = save && 1;

                save = save << 16;
                newq2 = (s->quad_2)&pdb_cMasks[(zero+d)%8];
                newq2 = newq2 | save;
                nState = pdb_make_state(s->quad_1,newq2,zero+d, cost + s->cost);
            }
            break;
        case 3:
            // Estamos en la cuarta linea del puzzle
            save = (s->quad_2)&pdb_masks[(zero+d)%8];

            // Guardar el valor de la casilla destino para costo
            cost = save && 1;

            save = save >> 16;
            save = save&(0x0000FFFF);
            newq1 = (s->quad_2)&pdb_cMasks[(zero+d)%8];
            newq1 = newq1 | save;
            nState = pdb_make_state(s->quad_1,newq1,zero+d, cost + s->cost);
            break;
    }
}

/* FUNCION: pdb_transition
 * DESC   : Funcion para calcular la transicion de un estado a otro
 * s      : Estado a partir del cual hacer transicion
 * a      : Accion a realizar: 'l', 'r', 'd', 'u' (En ingles)
 * RETORNA: Un nuevo estado resultado de aplicar el movimiento a en s\
 */
pdb_state pdb_transition(pdb_state s, char a) {
    
    int save;
    int newq;
    int zero = s->zero;
    pdb_state nState = NULL;
    save = 0;
    newq = 0;

    // Siempre estamos moviendo el cero
    switch (a) {
        case 'l':
                // Movimiento hacia la izquierda
                if (zero%4 != 0) {
                    nState = pdb_moveLR(s,-1);
                }
                break;
        case 'r':
                // Movimiento hacia la derecha
                if ((zero+1)%4 != 0) {
                    nState = pdb_moveLR(s,1);
                }
                break;
        case 'd':
                // Movimiento hacia abajo
                if (zero+4 < 16) {
                    nState = pdb_moveUD(s,4);
                }
                break;
        case 'u':
                // Movimiento hacia arriba
                if (zero-4 >= 0) {
                    nState = pdb_moveUD(s,-4);
                }
                break;
    }
    return nState;
}

/* FUNCION: pdb_init
 * DESC   : Funcion para la inicializacion y creacion del estado raiz
 * RETORNA: Un nuevo estado asociado a la configuracion inicial suministrada
 */
pdb_state pdb_init(char* input){
    /*Inicializacion de las mascaras usadas para computar la representacion
     * de la cuadricula*/
    pdb_initializeMasks();
    pdb_initializeCompMasks();
    printf("lainstancia actual es %s",input);
    
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
   
    return pdb_make_state(quad_1,quad_2,pos_zero, 0);
}

/* FUNCION: pdb_get_succ
 * DESC   : Funcion que obtiene todos los sucesores de un estado
 * s      : Estado del cual extraer los sucesores
 * RETORNA: Un arreglo con los sucesores del estado s
 */
pdb_successors pdb_get_succ(pdb_state s) {
    pdb_successors res = malloc(sizeof(struct _pdb_successors));
    res->succ[0] = pdb_transition(s,'l');
    res->succ[1] = pdb_transition(s,'r');
    res->succ[2] = pdb_transition(s,'u');
    res->succ[3] = pdb_transition(s,'d');
    return res;
}

/* FUNCION: pdb_print_state
 * DESC   : Imprime en pantalla la representacion de un estado
 * s      : Estado que se va a imprimir
 */
void pdb_print_state(pdb_state s) {
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

        if (s -> zero == i) {
            printf(" X  "); 
        } else {

            // Imprimimos el valor haciendo los shift correspondientes
            printf("%2d  ", (((s->quad_1)&pdb_masks[i])>>d)&(0x0000000F));

        }
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

        if ((s -> zero - 8) == i) {
            printf(" X  ");
        } else {
            // Imprimimos el valor haciendo los shift correspondientes
            printf("%2d  ", (((s->quad_2)&pdb_masks[i])>>d)&(0x0000000F));
        }

        // Se decrementa la cantidad de bits a mover en la siguiente iteracion
        d = d-4;
    }
    printf("\n");
}

/* FUNCION: pdb_free_state
 * DESC   : Libera el espacio reservado por un estado
 * s      : Estado a ser liberado
 */
void pdb_free_state(void *sp) {
    pdb_state s = (pdb_state) sp;
    free(s);
}
