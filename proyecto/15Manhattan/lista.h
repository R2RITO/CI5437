#ifndef FILE_LISTA
#define FILE_LISTA

typedef struct list_struct {

    void *first;
    void *last;
    int  size;

} *list;

/*
 * Crea una nueva lista vacia
 * @return Un apuntador a una nueva lista
 */
list newList();

/*
 * Destruye una lista y libera todo el espacio utilizado por ella
 * @param cList Es la lista que se va a destruir
 */
void freeList(list cList);

/*
 * Agrega un elemento en una lista
 * @param cList Es la lista en donde se va a agregar
 * @param elem  Es un apuntador al objeto que se va a agregar
 */
void addListElem(list cList, void *elem);

/*
 * Eliminar un elemento en una lista
 * @param cList Es la lista en donde se va a eliminar
 * @param elem  Es un apuntador al objeto que se va a eliminar
 * @para equal  Es una funcion que sirve para comparar elementos de la lista
 */
void rmListElem(list cList, void *elem, int (*equal)(void *a, void *b));

/*
 * Devuelve el tamanio de una lista
 * @param cList Es la lista que se va a consultar
 * @return El tamanio actual de la lista
 */
int  getListSize(list cList);

/*
 * Devuelve un elemento en una lista
 * @param cList Es la lista en donde se va a buscar
 * @param elem  Es un apuntador al objeto/identificador a buscar
 * @para equal  Es una funcion que sirve para comparar elementos de la lista
 * @return Devuelve el elemento completo si se encuentra. En otro caso retorna NULL
 */
void *getListElem(list cList, void *elem, int (*equal)(void *a, void *b));

/*
 * Imprime en pantalla la representacion de la lista
 * @param cList Es la lista que se va a imprimir
 */
void printList(list cList);

/*
 * Determina si una lista es vacia o no
 * @param cList Es la lista que se va a verificar
 * @return Cero si la lista es vacia, Entero positivo en caso contrario
 */
int emptyList(list cList);

/*
 * Elimina de la lista el elemento que se encuentre en la posicion index
 * @param cList Es la lista donde se va a eliminar
 */
void rmListElemByIndex(list cList, int index);

/*
 * Devuelve el elemento que se encuentra en la posicion index
 * @param cList Es la lista de donde se va a extraer el elemento
 */
void *getListElemByIndex(list cList, int index);

/*
 * Funcion que determina si dos strings son iguales
 * Creada para que reciba apuntadores a vacio
 * @param a Es un apuntador vacio que en realidad tiene un string
 * @param b Es un apuntador vacio que en realidad tiene un string
 * @return Retorna 0 solo si ambos Strings son iguales
 */ 
int stringEqual(void *a, void *b);

#endif
