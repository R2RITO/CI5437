#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "state.h"
#include <stdint.h>


/* Estructura para almacenar enteros en 32bits */
typedef struct _int64 {
    long long val : 64;
} int64;

/* Arreglo con patrones de cinco unos consecutivos para el primer cuadrante*/
int64 masks[14];

/* Arreglo con el complemento de cada patron del arreglo anterior*/
int64 cMasks[14];

/* Metodo para inicializar el arreglo de mascaras */
void initializeMasks() {

    /* El primer cuadrante va de 0 a 11, el segundo de 12 a 23, y la casilla
       24 esta representada en los ultimos 4 bits de la representacion del
       primer cuadrante, y el ultimo del segundo, y su mascara esta
       representada en las casillas 12 y 13 del arreglo de mascaras */
    
    masks[0].val  = 0xF800000000000000;
    masks[1].val  = 0x07C0000000000000;
    masks[2].val  = 0x003E000000000000;
    masks[3].val  = 0x0001F00000000000;
    masks[4].val  = 0x00000F8000000000;
    masks[5].val  = 0x0000007C00000000;
    masks[6].val  = 0x00000003E0000000;
    masks[7].val  = 0x000000001F000000;
    masks[8].val  = 0x0000000000F80000;
    masks[9].val  = 0x000000000007C000;
    masks[10].val = 0x0000000000003E00;
    masks[11].val = 0x00000000000001F0;
    masks[12].val = 0x000000000000000F;
    masks[13].val = 0x0000000000000001;


}

/* Metodo para inicializar el arreglo de complementos */
void initializeCompMasks() {
    
    cMasks[0].val  = 0x07FFFFFFFFFFFFFF;
    cMasks[1].val  = 0xF83FFFFFFFFFFFFF;
    cMasks[2].val  = 0xFFC1FFFFFFFFFFFF;
    cMasks[3].val  = 0xFFFE0FFFFFFFFFFF;
    cMasks[4].val  = 0xFFFFF07FFFFFFFFF;
    cMasks[5].val  = 0xFFFFFF83FFFFFFFF;
    cMasks[6].val  = 0xFFFFFFFC1FFFFFFF;
    cMasks[7].val  = 0xFFFFFFFFE0FFFFFF;
    cMasks[8].val  = 0xFFFFFFFFFF07FFFF;
    cMasks[9].val  = 0xFFFFFFFFFFF83FFF;
    cMasks[10].val = 0xFFFFFFFFFFFFC1FF;
    cMasks[11].val = 0xFFFFFFFFFFFFFE0F;
    cMasks[12].val = 0xFFFFFFFFFFFFFFF0;
    cMasks[13].val = 0xFFFFFFFFFFFFFFFE;
    
}

/* FUNCION: make_state
 * DESC   : Funcion para la creacion de un nuevo estado 
 * q1     : Representacion en entero de las primeras 8 casillas 
 * q2     : Representacion en entero de las ultimas 8 casillas
 * z      : Posicion actual del cero
 * RETORNA: Un nuevo esta con los valores q1 q2 y z
 */
 
state make_state(long long q1, long long q2, int z) {
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
    int64 q1;
    int64 q2;
    q1.val = 0x00443214C74254BC;
    q2.val = 0x635CF84653A56D70;
    return (q1.val==s->quad_1)&&(q2.val==s->quad_2);
}


/* FUNCION: moveLR
 * DESC   : Devuelve un estado resultado de mover el cero a la izquierda
 *          o a la derecha. El estado s no es alterado
 * s      : Estado a partir del cual se va a mover
 * d      : Desplazamiento hacia la izquierda o derecha del estado s
 * RETORNA: Un nuevo estado resultado de aplicar el desplazamiento d en s
 */
state moveLR(state s, int d) {
    
    int64 save;
    int64 newq1;
    int64 newq2;
    int64 aux;    
    int zero = s->zero;
    state nState = NULL;
    save.val = 0;
    newq1.val = 0;
    newq2.val = 0;
    aux.val = 0;    
    

    if (zero < 12) {
        // Si estamos en el primer cuadrante

        // Casilla 11 y movimiento a la derecha, cambio de cuadrante
        if ((zero == 11) && (d > 0)) {

            save.val = (s->quad_2) & masks[(zero+d)%12].val;
            save.val = (save.val) >> 55;
            save.val = (save.val) & (0x00000000000001FF);
        
            newq1.val = (s -> quad_1) | (save.val);
            newq2.val = (s -> quad_2) & cMasks[(zero+d)%12].val;

            nState = make_state(newq1.val,newq2.val,zero+d);          

        } else {
            save.val = (s->quad_1)&masks[zero+d].val;
            if ( d < 0 ) {
                // Si el movimiento es a la izquierda
                save.val = save.val >> 5;
                save.val = save.val & (0x07FFFFFFFFFFFFFF);
            } else {
                // Si el movimiento es a la derecha
                save.val = save.val << 5;
            }
            newq1.val = (s->quad_1) & cMasks[zero+d].val;
            newq1.val = (newq1.val) | (save.val);
            nState = make_state(newq1.val,s -> quad_2, zero+d);
        }

    } else {
        // Si estamos en el segundo cuadrante

        if ( (zero == 12) && (d < 0) ) {

            save.val = (s -> quad_1) & masks[(zero+d)%12].val;
            save.val = (save.val) << 55;

            newq1.val = (s -> quad_1) & cMasks[(zero+d)%12].val;
            newq2.val = (s -> quad_2) | save.val;

            nState = make_state(newq1.val, newq2.val, zero+d);

        } else if ( zero == 24 ) {

            save.val = (s -> quad_2) & masks[(zero+d)%12].val;
            save.val = (save.val) >> 4;
            save.val = (save.val) & (0x0FFFFFFFFFFFFFFF);

            // Copiar los 4 bits de la casilla 24 al primer cuadrante
            aux.val = save.val >> 1;
            aux.val = (aux.val) & (0x7FFFFFFFFFFFFFFF);
            newq1.val = (s -> quad_1) & cMasks[12].val;
            newq1.val = (newq1.val) | (aux.val);
            
            // Ahora copiar el ultimo bit de la casilla 24 al segundo cuadrante
    
            aux.val = (save.val) & masks[13].val;       
            newq2.val = (s -> quad_2) & cMasks[13].val;
            newq2.val = (newq2.val) | (aux.val);

            // Mover el cero

            newq2.val = (newq2.val) & cMasks[(zero+d)%12].val;

            nState = make_state(newq1.val, newq2.val, zero+d);
        
        } else if ((zero == 23) && (d > 0)) {


            // Tomar los ultimos 4 bits del primer cuadrante (casilla 24)
            save.val = (s -> quad_1) & masks[12].val;

            /* Hacer shift hacia la izquierda para posicionar los 4 bits
               de manera correcta, y hacer espacio para el 5to bit */
            save.val = (save.val) << 1;

            // Tomar el ultimo bit del segundo cuadrante (casilla 24)
            save.val = (save.val) | ((s -> quad_2) & masks[13].val);
            
            /* En "save" esta el valor de la casilla 24, ahora hay que mover
               el cero y copiar el valor en la casilla 23 */
            
            newq2.val = (s -> quad_2) | ((save.val) << 4);

            /* Mover el cero */

            newq1.val = (s -> quad_1) & cMasks[12].val;
            newq2.val = newq2.val & cMasks[13].val;

            nState = make_state(newq1.val, newq2.val, zero+d);


        } else {

            save.val = (s -> quad_2) & masks[(zero+d)%12].val;

            if ( d < 0 ) {
                // Si el movimiento es a la izquierda
                save.val = (save.val) >> 5;
                save.val = (save.val) & (0x07FFFFFFFFFFFFFF);
            } else {
                // Si el movimiento es a la derecha
                save.val = save.val << 5;
            }
            newq2.val = (s -> quad_2) & cMasks[(zero+d)%12].val;
            newq2.val = (newq2.val) | save.val;
            nState = make_state(s -> quad_1, newq2.val, zero+d);

        }

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

    int64 save;
    int64 aux;
    int64 newq1;
    int64 newq2;
    int zero = s->zero;
    state nState = NULL;
    save.val  = 0;
    aux.val   = 0;
    newq1.val = 0;
    newq2.val = 0;

    /* El desplazamiento (d) vale 5 o -5 y se cambia de acuerdo al
       caso, 5 es hacia abajo. -5 es hacia arriba. */
    
    if (zero < 12) {
        // Estamos en el primer cuadrante
        
        if ((zero > 6) && (d > 0)) {
            // Hay cambio de cuadrante

            // Salvar el valor y ponerlo en posicion para guardar
            save.val = (s -> quad_2) & masks[(zero+d)%12].val;
            save.val = save.val >> 35;
            save.val = save.val & (0x000000001FFFFFFF);

            // Mover el cero
            newq2.val = (s -> quad_2) & cMasks[(zero+d)%12].val;

            // Copiar el valor salvado
            newq1.val = (s -> quad_1) | save.val;

            nState = make_state(newq1.val,newq2.val,zero+d);

        } else {
            // El movimiento solamente es en el primer cuadrante

            // Salvar el valor y ponerlo en posicion para guardar
            save.val = (s -> quad_1) & masks[(zero+d)%12].val;

            
            if (d > 0) {
                // Movimiento hacia abajo
                save.val = save.val << 25;
                
            } else {
                // Movimiento hacia arriba
                save.val = (save.val >> 25)&(0x0000007FFFFFFFFF);
            }

            // Mover el 0
            newq1.val = (s -> quad_1) & cMasks[(zero+d)%12].val;

            newq1.val = newq1.val | save.val;
            
            nState = make_state(newq1.val,s -> quad_2,zero+d);

        }

    } else {
        // Estamos en el segundo cuadrante
        
        if ((zero < 17) && (d < 0)) {
            // Hay cambio de cuadrante

            // Salvar el valor y ponerlo en posicion para guardar
            save.val = (s -> quad_1) & masks[(zero+d)%12].val;
            save.val = save.val << 35;
            
            // Mover el cero
            newq1.val = (s -> quad_1) & cMasks[(zero+d)%12].val;

            // Copiar el valor salvado
            newq2.val = (s -> quad_2) | save.val;

            nState = make_state(newq1.val,newq2.val,zero+d);


        } else if (zero == 24) {
            // Movimiento desde la casilla 24, caso especial
            
            // Salvar el valor y ponerlo en posicion para guardar
            save.val = (s -> quad_2) & masks[(zero+d)%12].val;
            save.val = (save.val >> 24) & (0x000000FFFFFFFFFF);

            // Guardar los primeros 4 bits
            aux.val = (save.val >> 1) & (0x7FFFFFFFFFFFFFFF);

            newq1.val = (s -> quad_1) & cMasks[12].val;
            newq1.val = (newq1.val) | (aux.val);

            // Ahora copiar el ultimo bit de la casilla 24 al segundo cuadrante
    
            aux.val = (save.val) & masks[13].val;       
            newq2.val = (s -> quad_2) & cMasks[13].val;
            newq2.val = (newq2.val) | (aux.val);

            // Mover el cero

            newq2.val = (newq2.val) & cMasks[(zero+d)%12].val;

            nState = make_state(newq1.val, newq2.val, zero+d);


        } else if ((zero == 19) && (d > 0)) {
            // Movimiento hacia la casilla 24, caso especial

            // Tomar los ultimos 4 bits del primer cuadrante (casilla 24)
            save.val = (s -> quad_1) & masks[12].val;

            /* Hacer shift hacia la izquierda para posicionar los 4 bits
               de manera correcta, y hacer espacio para el 5to bit */
            save.val = (save.val) << 1;

            // Tomar el ultimo bit del segundo cuadrante (casilla 24)
            save.val = (save.val) | ((s -> quad_2) & masks[13].val);
            
            /* En "save" esta el valor de la casilla 24, ahora hay que mover
               el cero y copiar el valor en la casilla 23 */
            
            newq2.val = (s -> quad_2) | ((save.val) << 24);

            /* Mover el cero */

            newq1.val = (s -> quad_1) & cMasks[12].val;
            newq2.val = newq2.val & cMasks[13].val;

            nState = make_state(newq1.val, newq2.val, zero+d);
        
        } else {
            // Resto de los casos, movimiento en segundo cuadrante.

            // Salvar el valor y ponerlo en posicion para guardar
            save.val = (s -> quad_2) & masks[(zero+d)%12].val;
            
            if (d > 0) {
                // Movimiento hacia abajo
                save.val = save.val << 25;
                
            } else {
                // Movimiento hacia arriba
                save.val = (save.val >> 25)&(0x0000001FFFFFFFFF);
            }

            // Mover el 0
            newq2.val = (s -> quad_2) & cMasks[(zero+d)%12].val;

            newq2.val = newq2.val | save.val;
            
            nState = make_state(s -> quad_1,newq2.val,zero+d);

        }

    }

    return nState;

}



/* FUNCION: transition
 * DESC   : Funcion para calcular la transicion de un estado a otro
 * s      : Estado a partir del cual hacer transicion
 * a      : Accion a realizar: 'l', 'r', 'd', 'u' (En ingles)
 * RETORNA: Un nuevo estado resultado de aplicar el movimiento a en s\
 */
state transition(state s, char a) {

    int64 save;
    int64 newq;
    int zero = s->zero;
    state nState = s;
    save.val = 0;
    newq.val = 0;

    // Siempre estamos moviendo el cero
    switch (a) {
        case 'l':
                // Movimiento hacia la izquierda
                if (zero%5 != 0) {
                    nState = moveLR(s,-1);
                }
                break;
        case 'r':
                // Movimiento hacia la derecha
                if ((zero+1)%5 != 0) {
                    nState = moveLR(s,1);
                }
                break;
        case 'd':
                // Movimiento hacia abajo
                if (zero+5 < 25) {
                    nState = moveUD(s,5);
                }
                break;
        case 'u':
                // Movimiento hacia arriba
                if (zero-5 >= 0) {
                    nState = moveUD(s,-5);
                }
                break;

    }
    return nState;
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
    int d = 59;

    // Imprimimos el primer cuadrante
    for (i=0; i<12; i++) {
        // Salto de linea cada vez que se termina de imprimir una linea
        if (i%5 == 0) {
            printf("\n");
        }
        // Imprimimos el valor haciendo los shift correspondientes 
        printf("%2lld  ", (((s->quad_1)&masks[i].val)>>d)&0x000000000000001F);
        // Se decrementa la cantidad de bits a mover en la siguiente iteracion
        d = d-5;
    }
    // Reinicializamos el numero de bits a mover
    d = 59;

    // Imprimimos el segundo cuadrante
    for (i=12; i<24; i++) {
        // Salto de linea cada vez que se termina de imprimir una linea
        if (i%5 == 0) {
            printf("\n");
        }
        // Imprimimos el valor haciendo los shift correspondientes
        printf("%2lld  ", (((s->quad_2)&masks[i%12].val)>>d)&0x000000000000001F);
        // Se decrementa la cantidad de bits a mover en la siguiente iteracion
        d = d-5;
    }

    // Imprimir la casilla 24
    int64 aux;
    aux.val = ((s -> quad_1) & masks[12].val) << 1;
    aux.val = aux.val | ((s -> quad_2) & masks[13].val);

    printf("%2lld  ", aux.val);

    printf("\n");
}


main() {
    printf("Hola\n");

    initializeMasks();
    initializeCompMasks();

    state s;
    state news;
    int64 q1;
    int64 q2;

/*
    q1.val = 0x00443214C74254BC;
    q2.val = 0x635CF84653A56D70;

    s = make_state(q1.val,q2.val,0);
    print_state(s);

    news = transition(s,'d');
    print_state(news);

    news = transition(news,'u');
    print_state(news);


    int i = 0;
    for (i=0; i<7; i++) {
        news = transition(news,'d');
        print_state(news);
    }

*/

/*
    q1.val = 0x58443214C742540C;
    q2.val = 0x635CF84653A56D70;

    s = make_state(q1.val,q2.val,11);
    print_state(s);

    news = transition(s,'d');
    print_state(news);

    news = transition(news,'u');
    print_state(news);
*/


    printf("Prueba del 24 \n");

    q1.val = 0xC0443214C74254B0;
    q2.val = 0x635CF84653A56D70;

    s = make_state(q1.val,q2.val,24);
    print_state(s);

    news = transition(s,'u');
    print_state(news);

    news = transition(news,'d');
    print_state(news);


}
