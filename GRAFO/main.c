/**
* @file
* @author  Arturo Voltattorni, Fernando D'agostino & Oswaldo Jimenez 
*
* @section Descripcion
*
* Main: Ejecucion de funciones y salida de datos.
*/

#include  "Grafo.h"
#include  "Queue.h"

/**
* Main de pruebas
*/
void main() {
   printf("Creando Grafo cuyos elementos son del tipo PRUEBA...\n");
   grafo mi_grafo = newGrafo(newPrueba,freePrueba,print_prueba,compare_prueba);
   
   printf("\nCreando elementos tipo PRUEBA...\n");
   PRUEBA* prueba1 = newPrueba("Madona");
   print_prueba(prueba1);
   
   PRUEBA* prueba2 = newPrueba("Ariel");
   print_prueba(prueba2);
   
   PRUEBA* prueba3 = newPrueba("Cenicienta");
   print_prueba(prueba3);
   
   PRUEBA* prueba4 = newPrueba("LaNegra");
   print_prueba(prueba4);
 
 
   printf("\nCreando nodos del grafo para cada elemento...\n");  
   nodo nodo1 = newNodo(prueba1);
   nodoPrint(nodo1,print_prueba);
   
   nodo nodo2 = newNodo(prueba2);
   nodoPrint(nodo2,print_prueba);
   
   nodo nodo3 = newNodo(prueba3);
   nodoPrint(nodo3,print_prueba);
   
   nodo nodo4 = newNodo(prueba4);
   nodoPrint(nodo4,print_prueba);
   
   
   printf("\nCreando arcos...\n");  
    
   arco arquito    = newArco(nodo1,nodo2);
   arco arquitoInv = newArco(nodo2,nodo1);
   arco arc        = newArco(nodo1,nodo3);
   
   printArco(arquito,print_prueba);
   printf("\n Salto de linea \n");
   printArco(arquitoInv,print_prueba);
   printArco(arc,print_prueba);
   printf("\n Salto de linea \n");

   printf("Comparacion 1: (ESPERADO [1]) %d \nComparacion 2: (ESPERADO [0]) %d \n",
           arcoEquals(arc,arc,compare_prueba),arcoEquals(arquito,arc,compare_prueba));
 
   freeNodo(nodo1,freePrueba);
   freeNodo(nodo2,freePrueba);
   freeNodo(nodo3,freePrueba);
   freeNodo(nodo4,freePrueba);
   freeArco(arquito);
   freeArco(arquitoInv);
   freeArco(arc);  
   freeGrafo(mi_grafo);
   
/******************************************************************************/
/****************************** PRUEBA COLA  **********************************/
/******************************************************************************/   
 
 
   QUEUE* queue = create_queue();
   printf("Tam de creacion: (ESPERADO [0]) %d \n",getSize(queue));  
   printf("Es Vacia la cola?: (ESPERADO [1]) %d \n",isEmpty(queue));
   
   print_queue_from_top(queue,print_prueba);

   print_queue_from_bottom(queue,print_prueba);
   
   printf("\nCreando elementos tipo PRUEBA...\n");
   prueba1 = newPrueba("Madona");
   print_prueba(prueba1);
   
   prueba2 = newPrueba("Ariel");
   print_prueba(prueba2);
   
   prueba3 = newPrueba("Cenicienta");
   print_prueba(prueba3);
   
   prueba4 = newPrueba("LaNegra");
   print_prueba(prueba4);
 
    
   printf("\nEncolando el primer elemento tipo PRUEBA prueba1...\n");
   
   enqueue(queue,prueba1);
   
   
   printf("\nImprimiendo hacia adelante y hacia atras...\n");
   print_queue_from_top(queue,print_prueba);
   print_queue_from_bottom(queue,print_prueba);
   
   printf("\nEncolando pruebas prueba2..prueba4...\n");
   
   enqueue(queue,prueba2);
   enqueue(queue,prueba3);
   enqueue(queue,prueba4);
   
   printf("\nImprimiendo hacia adelante y hacia atras...\n");
   print_queue_from_top(queue,print_prueba);
   print_queue_from_bottom(queue,print_prueba);
   
    printf("\nDesencolando un elemento (prueba1)...\n");
   
   dequeue(queue);
   printf("\nImprimiendo hacia adelante y hacia atras...\n");
   print_queue_from_top(queue,print_prueba);
   print_queue_from_bottom(queue,print_prueba);
   
   
  
   printf("\nLimpiando el resto de la cola...\n");
   clear(queue); 
   printf("\nImprimiendo hacia adelante y hacia atras...\n");
   print_queue_from_top(queue,print_prueba);
   print_queue_from_bottom(queue,print_prueba);
   
   erase_queue(queue);
   freePrueba(prueba1);
   freePrueba(prueba2);
   freePrueba(prueba3);
   freePrueba(prueba4);
   
}
