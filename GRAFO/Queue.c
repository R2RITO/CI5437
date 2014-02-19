/**
* @file
* @author  Arturo Voltattorni, Fernando D'agostino & Oswaldo Jimenez 
*
* @section Descripcion
*
* Especificacion e implementacion del TAD cola.
*/

#include "Queue.h"

/** 
* Crea una estructura dinamica cola, se
* reseva su espacio de memoria
* @return La cola creada 
*/
QUEUE* create_queue(void) {
	
     /* Valores de inicializacion de la cola*/	
     QUEUE* new_queue = (QUEUE*)malloc(sizeof(QUEUE)) ;
     new_queue->size     = 0;
     new_queue->top      = NULL; 
     new_queue->bottom   = NULL;
     return new_queue;
}

/** 
* Elimina una estructura dinamica cola, se
* libera su espacio de memoria.
* @param q la cola a liberar
*/
void erase_queue(QUEUE* q) {

    /*La cola solo puede ser eliminada si esta esta vacia*/
    if (!isEmpty(q)){
        printf("La cola no esta vacia, no puede ser eliminada.");
        return;
    }
    free(q);
}

/** 
* Indica si la cola no contiene elementos
* @param q Estructura cola de entrada
* @return 1 si la cola esta vacia, 0 en caso contrario
*/
int isEmpty(QUEUE *q){
    return (q->size == 0);
}

/** 
* Retorna la cardinalidad de la cola
* @param q Estructura cola de entrada
* @return Tamanio de la cola entrante
*/
int getSize(QUEUE *q){
    return q->size;
}

/** 
* Encola un elemento en la cola
* @param q Cola a encolar
* @param elem contenido a encolar
*/
void enqueue (QUEUE *q, void *elem) {

    /*reserva del espacio de memoria del nuevo nodo*/
    QUEUE_NODE *new_queue_node = (QUEUE_NODE *)malloc(sizeof(QUEUE_NODE));

     /*inicializacion de elementos del nuevo nodo*/
     new_queue_node->contenido = elem;
     new_queue_node->next      = NULL;
     new_queue_node->front     = NULL;

     /*caso en el que la caja a insertar en la cola es la primera*/
     if (q->size == 0){
     
        /*se asigna el nuevo nodo al tope de la cola*/
        q->top = new_queue_node; 
     }
     
     /*en caso de que haya al menos un elemento, el apuntador
     * del 'fondo' debe ser actualizado, a fin de contemplar la
     * expansion de la cola
     */
     else {
         QUEUE_NODE* old_bottom = q->bottom;
         
         /*el precedesor del viejo fondo apuntara al nuevo nodo*/
         old_bottom->front      = new_queue_node;
         
         /*el sucedor del nuevo nodo apuntara al viejo fondo*/
         new_queue_node->next   = old_bottom;
     } 

     /*para cualquier caso el nuevo nodo correspondera al nuevo 'fondo'
      *de la cola*/
     q->bottom = new_queue_node; 
     
     /*se incermenta el tamanio de la cola*/
     q->size++;
}

/** 
* Desencola un elemento de la cola
* @param q Cola a desencolar
*/
void dequeue (QUEUE *q) {
     QUEUE_NODE *old_top;
     QUEUE_NODE *new_top;
     /*si la cola es vacia no se efectua ninguna operacion*/
     if(!isEmpty(q)){
     
         /*se guarda la referencia al tope de la cola*/
         old_top = q->top;
         
         /*Se actualiza el tope de la cola. Se apuntara al precedesor 
          *del viejo tope*/
         new_top = old_top->front;
         if (new_top!=NULL){ 
            new_top->next = NULL;
         }
         q->top  = new_top;
         
         /*Se desaloja del nodo referenciado por el viejo tope*/
         free(old_top); 
         
         /*se decrementa el tamanio de la cola*/
         q->size--;
         
         /*caso en que la cola queda vacia despues de desencolar*/
         if (q->size == 0){
             /*la cola queda como recien creada*/  
             q->top    = NULL;
             q->bottom = NULL;          
         }
     } //endif isEmpty
}

/** 
* Se eliminan y liberan los elementos de la cola
* y queda como recien creada
* @param q Cola a resetear
*/
void clear(QUEUE *q){
   /* 
	* Bucle que desencola elementos 1 a 1 hasta
	* que la cola este totalmente vacia
	*/
    while (!(isEmpty(q))){
        dequeue(q);
    }
}

/** 
* Impresion de los elementos en la cola, desde el tope hacia el fondo,
* en esa direccion.
* @param q Cola a imprimir
* @param impresor es la funcion de impresion empleada por los nodos de la cola
*/
void print_queue_from_top(QUEUE *q,void *(*impresor) (void *)){
    
    if (isEmpty(q)){
        printf("La cola esta vacia.\n");
        return;
    }
 
    printf("{\nQUEUE: \n   Size: %d\n   Content: (Top to Bottom)\n",q->size);   
    QUEUE_NODE* current_queue_node = q->top;
    
    while (!(current_queue_node == NULL)){
        printf("\t");
        impresor(current_queue_node->contenido);
        current_queue_node = current_queue_node->front;
    }
    printf("}\n");
}

/** 
* Impresion de los elementos en la cola, desde el fondo hacia el tope,
* en esa direccion.
* @param q Cola a imprimir
* @param impresor es la funcion de impresion empleada por los nodos de la cola
*/
void print_queue_from_bottom(QUEUE *q,void *(*impresor) (void *)){
    
    if (isEmpty(q)){
        printf("La cola esta vacia.\n");
        return;
    }
    
    
    printf("{\nQUEUE: \n   Size: %d\n   Content: (Bottom to Top)\n",q->size);  
    QUEUE_NODE* current_queue_node = q->bottom;
    
    while (!(current_queue_node == NULL)){
        printf("\t");
        impresor(current_queue_node->contenido);
        current_queue_node = current_queue_node->next;
    }
    printf("}\n");
}
