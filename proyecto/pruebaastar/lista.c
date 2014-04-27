#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "caja.h"
#include "lista.h"

/*
 * Crea una nueva lista vacia
 * @return Un apuntador a una nueva lista
 */
list newList() {

    list nList = malloc(sizeof(struct list_struct));
    nList -> first = NULL;
    nList -> last  = NULL;
    nList -> size  = 0;
    return nList;
}


/*
 * Destruye una lista y libera todo el espacio utilizado por ella
 * @param cList Es la lista que se va a destruir
 */
void freeList(list cList) {

    box cBox;
    box rmBox;
    cBox = (cList -> first);
    
    while (cBox) {
        rmBox = cBox;
        cBox = getNextBox(cBox);
        freeBox(rmBox);
    }

    free(cList);
}

/*
 * Agrega un elemento en una lista
 * @param cList Es la lista en donde se va a agregar
 * @param elem  Es un apuntador al objeto que se va a agregar
 */
void addListElem(list cList, void *elem) {

    box nBox = newBox();
    setElemBox(nBox, elem);

    if (!(cList -> size)) {
        cList -> first = nBox;
        cList -> last  = nBox;
    } else {
        box lastBox = (cList -> last);
        setNextBox(lastBox, nBox);
        setPrevBox(nBox, lastBox);
        setNextBox(nBox, NULL);
        cList -> last = nBox;
    }
    ++(cList -> size);
}

/*
 * Eliminar un elemento en una lista
 * @param cList Es la lista en donde se va a eliminar
 * @param elem  Es un apuntador al objeto que se va a eliminar
 * @para equal  Es una funcion que sirve para comparar elementos de la lista
 */
void rmListElem(list cList, void *elem, int (*equal)(void *a, void *b)) {

    box cBox = cList -> first;
    
    while (cBox) {

        if (equal(elem, (cBox -> elem)) == 0) {
            
            box prev = getPrevBox(cBox);
            box next = getNextBox(cBox);
            freeBox(cBox);
            
            if (prev) {
                setNextBox(prev, next);
                if (!next)
                    cList -> last = prev;
            }

            if (next) {
                setPrevBox(next, prev);
                if (!prev)
                    cList -> first = next;
            }

            if ((!prev) && (!next)) {
                cList -> first = NULL;
                cList -> last  = NULL;
            }

            --(cList -> size);            

            return;   
        }
        cBox = getNextBox(cBox);
    }
}

/*
 * Devuelve un elemento en una lista
 * @param cList Es la lista en donde se va a buscar
 * @param elem  Es un apuntador al objeto/identificador a buscar
 * @para equal  Es una funcion que sirve para comparar elementos de la lista
 * @return Devuelve el elemento completo si se encuentra. En otro caso retorna NULL
 */
void *getListElem(list cList, void *elem, int (*equal)(void *a, void *b)) {

    box cBox = cList -> first;

    while (cBox) {

        if (equal(elem, (cBox -> elem)) == 0) {
            return (cBox -> elem);
        }
        cBox = getNextBox(cBox);
    }
    return NULL;
}

/*
 * Devuelve el tamanio de una lista
 * @param cList Es la lista que se va a consultar
 * @return El tamanio actual de la lista
 */
int getListSize(list cList) {
    if (cList == NULL) return 0;
    return (cList -> size);
}

/*
 * Imprime en pantalla la representacion de la lista
 * @param cList Es la lista que se va a imprimir
 */
void printList(list cList) {

    box cBox = (cList -> first);
    while (cBox) {
        printBox(cBox);
        cBox = getNextBox(cBox);
    }
}

/*
 * Determina si una lista es vacia o no
 * @param cList Es la lista que se va a verificar
 * @return Cero si la lista es vacia, Entero positivo en caso contrario
 */
int emptyList(list cList) {
    if (cList == NULL) return 0;
    return (cList -> size);
}

/*
 * Elimina de la lista el elemento que se encuentre en la posicion index
 * @param cList Es la lista donde se va a eliminar
 */
void rmListElemByIndex(list cList, int index) {

    int size = (cList -> size);

    if ((size==0) || (index < 0) || (index >= size))
        return;

    box cBox = (cList -> first);
    int i;
    for (i = 0; i < index; i++) {
        cBox = getNextBox(cBox);
    }

    box prev = getPrevBox(cBox);
    box next = getNextBox(cBox);
    freeBox(cBox);

    if (prev) {
        setNextBox(prev, next);
        if (!next)
            cList -> last = prev;
    }

    if (next) {
        setPrevBox(next, prev);
        if (!prev)
            cList -> first = next;
    }

    if ((!prev) && (!next)) {
        cList -> first = NULL;
        cList -> last  = NULL;
    }

    --(cList -> size);
    return;

}

/*
 * Devuelve el elemento que se encuentra en la posicion index
 * @param cList Es la lista de donde se va a extraer el elemento
 * @return NULL si la lista es vacia o el index esta fuera del rango
 * En caso contrario, un apuntador al elemento solicitado
 */
void *getListElemByIndex(list cList, int index) {

    int size = (cList -> size);

    if ((size==0) || (index < 0) || (index >= size))
        return NULL;

    box cBox = (cList -> first);
    int i;
    for (i = 0; i < index; i++) {
        cBox = getNextBox(cBox);
    }

    return (cBox -> elem);
}

/*
 * Funcion que determina si dos strings son iguales
 * Creada para que reciba apuntadores a vacio
 * @param a Es un apuntador vacio que en realidad tiene un string
 * @param b Es un apuntador vacio que en realidad tiene un string
 * @return Retorna 0 solo si ambos Strings son iguales
 */ 
int stringEqual(void *a, void *b) {

    char *sa = a;
    char *sb = b;
    return strcmp(sa, sb);
}
