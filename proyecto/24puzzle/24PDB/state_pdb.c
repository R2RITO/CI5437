#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "state_pdb.h"
#include <stdint.h>
#define BUFFER_SIZE 80

/* Estructura para almacenar enteros en 32bits */
typedef struct _int64 {
    long long val : 64;
} int64;


/* Metodo para inicializar el arreglo de mascaras */
void pdb_initializeMasks() {

    /* El primer cuadrante va de 0 a 11, el segundo de 12 a 23, y la casilla
       24 esta representada en los ultimos 4 bits de la representacion del
       primer cuadrante, y el ultimo del segundo, y su mascara esta
       representada en las casillas 12 y 13 del arreglo de mascaras */
    
    pdb_masks[0].val  = 0xF800000000000000;
    pdb_masks[1].val  = 0x07C0000000000000;
    pdb_masks[2].val  = 0x003E000000000000;
    pdb_masks[3].val  = 0x0001F00000000000;
    pdb_masks[4].val  = 0x00000F8000000000;
    pdb_masks[5].val  = 0x0000007C00000000;
    pdb_masks[6].val  = 0x00000003E0000000;
    pdb_masks[7].val  = 0x000000001F000000;
    pdb_masks[8].val  = 0x0000000000F80000;
    pdb_masks[9].val  = 0x000000000007C000;
    pdb_masks[10].val = 0x0000000000003E00;
    pdb_masks[11].val = 0x00000000000001F0;
    pdb_masks[12].val = 0x000000000000000F;
    pdb_masks[13].val = 0x0000000000000001;


}

/* Metodo para inicializar el arreglo de complementos */
void pdb_initializeCompMasks() {
    
    pdb_cMasks[0].val  = 0x07FFFFFFFFFFFFFF;
    pdb_cMasks[1].val  = 0xF83FFFFFFFFFFFFF;
    pdb_cMasks[2].val  = 0xFFC1FFFFFFFFFFFF;
    pdb_cMasks[3].val  = 0xFFFE0FFFFFFFFFFF;
    pdb_cMasks[4].val  = 0xFFFFF07FFFFFFFFF;
    pdb_cMasks[5].val  = 0xFFFFFF83FFFFFFFF;
    pdb_cMasks[6].val  = 0xFFFFFFFC1FFFFFFF;
    pdb_cMasks[7].val  = 0xFFFFFFFFE0FFFFFF;
    pdb_cMasks[8].val  = 0xFFFFFFFFFF07FFFF;
    pdb_cMasks[9].val  = 0xFFFFFFFFFFF83FFF;
    pdb_cMasks[10].val = 0xFFFFFFFFFFFFC1FF;
    pdb_cMasks[11].val = 0xFFFFFFFFFFFFFE0F;
    pdb_cMasks[12].val = 0xFFFFFFFFFFFFFFF0;
    pdb_cMasks[13].val = 0xFFFFFFFFFFFFFFFE;
    
}

/* FUNCION: pdb_make_state
 * DESC   : Funcion para la creacion de un nuevo estado 
 * q1     : Representacion en entero de las primeras 8 casillas 
 * q2     : Representacion en entero de las ultimas 8 casillas
 * z      : Posicion actual del cero
 * RETORNA: Un nuevo esta con los valores q1 q2 y z
 */
 
pdb_state pdb_make_state(long long q1, long long q2, int z) {
    pdb_state newState = malloc(sizeof(struct _pdb_state));
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
int pdb_is_goal(pdb_state s) {
    int64 q1;
    int64 q2;
    q1.val = 0x00443214C74254BC;
    q2.val = 0x635CF84653A56D70;
    return (q1.val==s->quad_1)&&(q2.val==s->quad_2);
}


/* FUNCION: pdb_moveLR
 * DESC   : Devuelve un estado resultado de mover el cero a la izquierda
 *          o a la derecha. El estado s no es alterado
 * s      : Estado a partir del cual se va a mover
 * d      : Desplazamiento hacia la izquierda o derecha del estado s
 * RETORNA: Un nuevo estado resultado de aplicar el desplazamiento d en s
 */
pdb_state pdb_moveLR(pdb_state s, int d) {
    
    int64 save;
    int64 newq1;
    int64 newq2;
    int64 aux;    
    int zero = s->zero;
    pdb_state nState = NULL;
    save.val = 0;
    newq1.val = 0;
    newq2.val = 0;
    aux.val = 0;    
    

    if (zero < 12) {
        // Si estamos en el primer cuadrante

        // Casilla 11 y movimiento a la derecha, cambio de cuadrante
        if ((zero == 11) && (d > 0)) {

            save.val = (s->quad_2) & pdb_masks[(zero+d)%12].val;
            save.val = (save.val) >> 55;
            save.val = (save.val) & (0x00000000000001FF);
        
            newq1.val = (s -> quad_1) | (save.val);
            newq2.val = (s -> quad_2) & pdb_cMasks[(zero+d)%12].val;

            nState = pdb_make_state(newq1.val,newq2.val,zero+d);          

        } else {
            save.val = (s->quad_1)&pdb_masks[zero+d].val;
            if ( d < 0 ) {
                // Si el movimiento es a la izquierda
                save.val = save.val >> 5;
                save.val = save.val & (0x07FFFFFFFFFFFFFF);
            } else {
                // Si el movimiento es a la derecha
                save.val = save.val << 5;
            }
            newq1.val = (s->quad_1) & pdb_cMasks[zero+d].val;
            newq1.val = (newq1.val) | (save.val);
            nState = pdb_make_state(newq1.val,s -> quad_2, zero+d);
        }

    } else {
        // Si estamos en el segundo cuadrante

        if ( (zero == 12) && (d < 0) ) {

            save.val = (s -> quad_1) & pdb_masks[(zero+d)%12].val;
            save.val = (save.val) << 55;

            newq1.val = (s -> quad_1) & pdb_cMasks[(zero+d)%12].val;
            newq2.val = (s -> quad_2) | save.val;

            nState = pdb_make_state(newq1.val, newq2.val, zero+d);

        } else if ( zero == 24 ) {

            save.val = (s -> quad_2) & pdb_masks[(zero+d)%12].val;
            save.val = (save.val) >> 4;
            save.val = (save.val) & (0x0FFFFFFFFFFFFFFF);

            // Copiar los 4 bits de la casilla 24 al primer cuadrante
            aux.val = save.val >> 1;
            aux.val = (aux.val) & (0x7FFFFFFFFFFFFFFF);
            newq1.val = (s -> quad_1) & pdb_cMasks[12].val;
            newq1.val = (newq1.val) | (aux.val);
            
            // Ahora copiar el ultimo bit de la casilla 24 al segundo cuadrante
    
            aux.val = (save.val) & pdb_masks[13].val;       
            newq2.val = (s -> quad_2) & pdb_cMasks[13].val;
            newq2.val = (newq2.val) | (aux.val);

            // Mover el cero

            newq2.val = (newq2.val) & pdb_cMasks[(zero+d)%12].val;

            nState = pdb_make_state(newq1.val, newq2.val, zero+d);
        
        } else if ((zero == 23) && (d > 0)) {


            // Tomar los ultimos 4 bits del primer cuadrante (casilla 24)
            save.val = (s -> quad_1) & pdb_masks[12].val;

            /* Hacer shift hacia la izquierda para posicionar los 4 bits
               de manera correcta, y hacer espacio para el 5to bit */
            save.val = (save.val) << 1;

            // Tomar el ultimo bit del segundo cuadrante (casilla 24)
            save.val = (save.val) | ((s -> quad_2) & pdb_masks[13].val);
            
            /* En "save" esta el valor de la casilla 24, ahora hay que mover
               el cero y copiar el valor en la casilla 23 */
            
            newq2.val = (s -> quad_2) | ((save.val) << 4);

            /* Mover el cero */

            newq1.val = (s -> quad_1) & pdb_cMasks[12].val;
            newq2.val = newq2.val & pdb_cMasks[13].val;

            nState = pdb_make_state(newq1.val, newq2.val, zero+d);


        } else {

            save.val = (s -> quad_2) & pdb_masks[(zero+d)%12].val;

            if ( d < 0 ) {
                // Si el movimiento es a la izquierda
                save.val = (save.val) >> 5;
                save.val = (save.val) & (0x07FFFFFFFFFFFFFF);
            } else {
                // Si el movimiento es a la derecha
                save.val = save.val << 5;
            }
            newq2.val = (s -> quad_2) & pdb_cMasks[(zero+d)%12].val;
            newq2.val = (newq2.val) | save.val;
            nState = pdb_make_state(s -> quad_1, newq2.val, zero+d);

        }

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

    int64 save;
    int64 aux;
    int64 newq1;
    int64 newq2;
    int zero = s->zero;
    pdb_state nState = NULL;
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
            save.val = (s -> quad_2) & pdb_masks[(zero+d)%12].val;
            save.val = save.val >> 35;
            save.val = save.val & (0x000000001FFFFFFF);

            // Mover el cero
            newq2.val = (s -> quad_2) & pdb_cMasks[(zero+d)%12].val;

            // Copiar el valor salvado
            newq1.val = (s -> quad_1) | save.val;

            nState = pdb_make_state(newq1.val,newq2.val,zero+d);

        } else {
            // El movimiento solamente es en el primer cuadrante

            // Salvar el valor y ponerlo en posicion para guardar
            save.val = (s -> quad_1) & pdb_masks[(zero+d)%12].val;

            
            if (d > 0) {
                // Movimiento hacia abajo
                save.val = save.val << 25;
                
            } else {
                // Movimiento hacia arriba
                save.val = (save.val >> 25)&(0x0000007FFFFFFFFF);
            }

            // Mover el 0
            newq1.val = (s -> quad_1) & pdb_cMasks[(zero+d)%12].val;

            newq1.val = newq1.val | save.val;
            
            nState = pdb_make_state(newq1.val,s -> quad_2,zero+d);

        }

    } else {
        // Estamos en el segundo cuadrante
        
        if ((zero < 17) && (d < 0)) {
            // Hay cambio de cuadrante

            // Salvar el valor y ponerlo en posicion para guardar
            save.val = (s -> quad_1) & pdb_masks[(zero+d)%12].val;
            save.val = save.val << 35;
            
            // Mover el cero
            newq1.val = (s -> quad_1) & pdb_cMasks[(zero+d)%12].val;

            // Copiar el valor salvado
            newq2.val = (s -> quad_2) | save.val;

            nState = pdb_make_state(newq1.val,newq2.val,zero+d);


        } else if (zero == 24) {
            // Movimiento desde la casilla 24, caso especial
            
            // Salvar el valor y ponerlo en posicion para guardar
            save.val = (s -> quad_2) & pdb_masks[(zero+d)%12].val;
            save.val = (save.val >> 24) & (0x000000FFFFFFFFFF);

            // Guardar los primeros 4 bits
            aux.val = (save.val >> 1) & (0x7FFFFFFFFFFFFFFF);

            newq1.val = (s -> quad_1) & pdb_cMasks[12].val;
            newq1.val = (newq1.val) | (aux.val);

            // Ahora copiar el ultimo bit de la casilla 24 al segundo cuadrante
    
            aux.val = (save.val) & pdb_masks[13].val;       
            newq2.val = (s -> quad_2) & pdb_cMasks[13].val;
            newq2.val = (newq2.val) | (aux.val);

            // Mover el cero

            newq2.val = (newq2.val) & pdb_cMasks[(zero+d)%12].val;

            nState = pdb_make_state(newq1.val, newq2.val, zero+d);


        } else if ((zero == 19) && (d > 0)) {
            // Movimiento hacia la casilla 24, caso especial

            // Tomar los ultimos 4 bits del primer cuadrante (casilla 24)
            save.val = (s -> quad_1) & pdb_masks[12].val;

            /* Hacer shift hacia la izquierda para posicionar los 4 bits
               de manera correcta, y hacer espacio para el 5to bit */
            save.val = (save.val) << 1;

            // Tomar el ultimo bit del segundo cuadrante (casilla 24)
            save.val = (save.val) | ((s -> quad_2) & pdb_masks[13].val);
            
            /* En "save" esta el valor de la casilla 24, ahora hay que mover
               el cero y copiar el valor en la casilla 23 */
            
            newq2.val = (s -> quad_2) | ((save.val) << 24);

            /* Mover el cero */

            newq1.val = (s -> quad_1) & pdb_cMasks[12].val;
            newq2.val = newq2.val & pdb_cMasks[13].val;

            nState = pdb_make_state(newq1.val, newq2.val, zero+d);
        
        } else {
            // Resto de los casos, movimiento en segundo cuadrante.

            // Salvar el valor y ponerlo en posicion para guardar
            save.val = (s -> quad_2) & pdb_masks[(zero+d)%12].val;
            
            if (d > 0) {
                // Movimiento hacia abajo
                save.val = save.val << 25;
                
            } else {
                // Movimiento hacia arriba
                save.val = (save.val >> 25)&(0x0000001FFFFFFFFF);
            }

            // Mover el 0
            newq2.val = (s -> quad_2) & pdb_cMasks[(zero+d)%12].val;

            newq2.val = newq2.val | save.val;
            
            nState = pdb_make_state(s -> quad_1,newq2.val,zero+d);

        }

    }

    return nState;

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



/* FUNCION: transition
 * DESC   : Funcion para calcular la transicion de un estado a otro
 * s      : Estado a partir del cual hacer transicion
 * a      : Accion a realizar: 'l', 'r', 'd', 'u' (En ingles)
 * RETORNA: Un nuevo estado resultado de aplicar el movimiento a en s\
 */
pdb_state transition(pdb_state s, char a) {

    int64 save;
    int64 newq;
    int zero = s->zero;
    pdb_state nState = s;
    save.val = 0;
    newq.val = 0;

    // Siempre estamos moviendo el cero
    switch (a) {
        case 'l':
                // Movimiento hacia la izquierda
                if (zero%5 != 0) {
                    nState = pdb_moveLR(s,-1);
                }
                break;
        case 'r':
                // Movimiento hacia la derecha
                if ((zero+1)%5 != 0) {
                    nState = pdb_moveLR(s,1);
                }
                break;
        case 'd':
                // Movimiento hacia abajo
                if (zero+5 < 25) {
                    nState = pdb_moveUD(s,5);
                }
                break;
        case 'u':
                // Movimiento hacia arriba
                if (zero-5 >= 0) {
                    nState = pdb_moveUD(s,-5);
                }
                break;

    }
    return nState;
}


/* FUNCION: init
 * DESC   : Funcion para la inicializacion y creacion del estado raiz
 * RETORNA: Un nuevo estado asociado a la configuracion inicial suministrada
 */
pdb_state pdb_init(char* input){
    /*Inicializacion de las mascaras usadas para computar la representacion
     * de la cuadricula*/
    pdb_initializeMasks();
    pdb_initializeCompMasks();
    printf("lainstancia actual es %s",input);
    
    int k[25];
    sscanf(input," %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d\n",
                   &k[0],&k[1],&k[2],&k[3],&k[4],&k[5],&k[6],&k[7],&k[8],
                   &k[9],&k[10],&k[11],&k[12],&k[13],&k[14],&k[15],&k[16],
                   &k[17],&k[18],&k[19],&k[20],&k[21],&k[22],&k[23],&k[24]);            
    
    int quad_index,quad_2_index;
    unsigned long long quad_1 = 0l; /*almacenamiento de la primera mitad de la cuadricula*/
    unsigned long long quad_2 = 0l; /*almacenamiento de la segunda mitad de la cuadricula*/
    unsigned int pos_zero = 0; /*posicion del 0 en la cuadricula*/
    for (quad_index=0; quad_index < 12; quad_index++){
        quad_2_index = quad_index+12;
       /*se recuerda la posicion del 0 en la cuadricula*/
       if (k[quad_index]==0) {
            pos_zero = quad_index;
       }
       if (k[quad_2_index]==0) {
            pos_zero = quad_2_index;
       }
       /*desplazamiento de los digitos significativos, permiten alojar el nuevo
        *numero entrante de 5 bits*/
       quad_1 = quad_1 << 5;
       quad_2 = quad_2 << 5;
       /*se conservan los bits encendidos de la cuadricula, agregando
        *la representacion binaria del numero entrante en los ultimos 5 bits*/
       quad_1 = quad_1 | k[quad_index];
       quad_2 = quad_2 | k[quad_2_index];
    }
    /*accedemos al numero restante en la cuadricula*/
    quad_2_index++;    

    if (k[quad_2_index]==0) {
         pos_zero = quad_2_index;
    }
    /*recuperamos los ultimos 4 bits del ultimo numero en la cuadricula*/
    unsigned long long last_4_bits_number = k[quad_2_index] >> 1;
    unsigned long long last_mask = 0xF;
    
    unsigned long long last_four_bits = last_4_bits_number & last_mask;
    
    /*se incorporan al primer cuadrante del tablero*/
    quad_1 = quad_1 << 4;
    quad_1   = quad_1|last_four_bits;
     /*recuperamos el ultimo bit del ultimo numero en la cuadricula*/
    unsigned long long last_number_bit    = k[quad_2_index] & pdb_masks[13].val; 
    
    /*se incorporan al segundo cuadrante del tablero*/
    quad_2 = quad_2 << 4;
    quad_2 = quad_2 |last_number_bit;
    
//     printf("%2lld\n",quad_2);
    return pdb_make_state(quad_1,quad_2,pos_zero);
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
    int d = 59;

    // Imprimimos el primer cuadrante
    for (i=0; i<12; i++) {
        // Salto de linea cada vez que se termina de imprimir una linea
        if (i%5 == 0) {
            printf("\n");
        }
        // Imprimimos el valor haciendo los shift correspondientes 
        printf("%2lld  ", (((s->quad_1)&pdb_masks[i].val)>>d)&0x000000000000001F);
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
        printf("%2lld  ", (((s->quad_2)&pdb_masks[i%12].val)>>d)&0x000000000000001F);
        // Se decrementa la cantidad de bits a mover en la siguiente iteracion
        d = d-5;
    }

    // Imprimir la casilla 24
    int64 aux;
    aux.val = ((s -> quad_1) & pdb_masks[12].val) << 1;
    aux.val = aux.val | ((s -> quad_2) & pdb_masks[13].val);

    printf("%2lld  ", aux.val);

    printf("\n");
}

int main(int argc, char *argv[]) {

    /*La invocacion debe tener exactamente 2 argumentos: el nombre del programa
     *y el archivo de entrada*/
    if (argc!=2) {
        printf("Modo de uso: ./main <nombre_archivo>\n");
        exit(1);
    }

    FILE *file;
    char* file_name = argv[1];
    char instance[BUFFER_SIZE];
    /*se hace apertura del archivo de entrada*/
    file = fopen(file_name,"r"); 
    if (!file) {
       perror("Error al abrir el archivo de entrada: ");
       exit(1);
    }
    /*resolucion linea por linea de las instancias suministradas en el
     *archivo de prueba*/
    while ( fgets (instance, BUFFER_SIZE, file)) {
        /*------------------ IDA* -------------------------*/
        pdb_state initial_state = pdb_init(instance);
        pdb_print_state(initial_state);
    }
}
