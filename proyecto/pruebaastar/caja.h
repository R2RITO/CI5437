#ifndef FILE_CAJA
#define FILE_CAJA

typedef struct box_struct {

    void *elem;
    void *next;
    void *prev;

} *box;

/* 
 * Crea una nueva caja completamente vacia
 */
box newBox();

/*
 * Destruye una caja y libera la memoria utilizada
 * @param cBox Es la caja que se va a destruir
 */
void freeBox(box cBox);

/*
 * Asigna un elemento dentro de una caja
 * @param cBox Es la caja que a la que se le va a asignar
 * @param elem Es un apuntado al elemento que se va a asignar
 */
void setElemBox(box cBox, void *elem);

/*
 * Obtiene el elemento contenido dentro de una caja
 * @param cBox Es la caja de donde se obtiene el elemento
 * @return El elemento contenido dentro de la caja
 */
void *getElemBox(box cBox);

/*
 * Le asigna a una caja el apuntador de su caja sucesora en la lista
 * @param cBox Es la caja que a la que se le va a asignar
 * @param next Es un apuntador a la caja que le sigue
 */
void setNextBox(box cBox, void *next);

/*
 * Obtiene el apuntador de la caja sucesora a una caja
 * @param cBox Es la caja de donde se obtiene el apuntador
 * @return Un apuntador a la siguiente caja
 */
void *getNextBox(box cBox);

/*
 * Le asigna a una caja el apuntador de su caja predecesora en la lista
 * @param cBox Es la caja que a la que se le va a asignar
 * @param prev Es un apuntador a la caja que le precede
 */
void setPrevBox(box cBox, void *prev);

/*
 * Obtiene el apuntador de la caja predecesora a una caja
 * @param cBox Es la caja de donde se obtiene el apuntador
 * @return Un apuntador a la caja anterior
 */
void *getPrevBox(box cBox);

/*
 * Imprime en pantalla los detalles de una caja
 * @param cBox Es la caja la cual se va a imprimir
 */
void printBox(box cBox);

#endif
