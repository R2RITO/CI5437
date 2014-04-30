#include <stdio.h>
#include <stdlib.h>
#include "caja.h"


/* 
 * Crea una nueva caja completamente vacia
 */
box newBox() {

    box nBox = malloc(sizeof(struct box_struct));
    nBox -> elem = NULL;
    nBox -> next = NULL;
    nBox -> prev = NULL;
    return nBox;
}

/*
 * Destruye una caja y libera la memoria utilizada
 * @param cBox Es la caja que se va a destruir
 */
void freeBox(box cBox) {

    cBox -> elem = NULL;
    cBox -> next = NULL;
    cBox -> prev = NULL;
    free(cBox);
}

/*
 * Asigna un elemento dentro de una caja
 * @param cBox Es la caja que a la que se le va a asignar
 * @param elem Es un apuntado al elemento que se va a asignar
 */
void setElemBox(box cBox, void *elem) {

    cBox -> elem = elem;
}

/*
 * Obtiene el elemento contenido dentro de una caja
 * @param cBox Es la caja de donde se obtiene el elemento
 * @return El elemento contenido dentro de la caja
 */
void *getElemBox(box cBox) {
    
    return (cBox -> elem);
}

/*
 * Le asigna a una caja el apuntador de su caja sucesora en la lista
 * @param cBox Es la caja que a la que se le va a asignar
 * @param next Es un apuntador a la caja que le sigue
 */
void setNextBox(box cBox, void *next) {

    cBox -> next = next;
}

/*
 * Obtiene el apuntador de la caja sucesora a una caja
 * @param cBox Es la caja de donde se obtiene el apuntador
 * @return Un apuntador a la siguiente caja
 */
void *getNextBox(box cBox) {

    return (cBox -> next);
}

/*
 * Le asigna a una caja el apuntador de su caja predecesora en la lista
 * @param cBox Es la caja que a la que se le va a asignar
 * @param prev Es un apuntador a la caja que le precede
 */
void setPrevBox(box cBox, void *prev) {

    cBox -> prev = prev;
}


/*
 * Obtiene el apuntador de la caja predecesora a una caja
 * @param cBox Es la caja de donde se obtiene el apuntador
 * @return Un apuntador a la caja anterior
 */
void *getPrevBox(box cBox) {

    return (cBox -> prev);
}

/*
 * Imprime en pantalla los detalles de una caja
 * @param cBox Es la caja la cual se va a imprimir
 */
void printBox(box cBox) {

    printf ("Box [ Elem: %s, Next: %d, Prev: %d ]\n", (*cBox).elem, (*cBox).next, (*cBox).prev);

}
