/**
* @file
* @author  Arturo Voltattorni, Fernando D'agostino & Oswaldo Jimenez 
*
* @section Descripcion
*
* Especificacion e implementacion del Tipo abstracto de datos Nodo.
*/

#include "Grafo.h"

/******************************************************************************/
/*********************** MANAGER DEL TAD GRAFO ********************************/
/******************************************************************************/

/**
* Creacion de un grafo. Se hace reserva de la memoria de la estructura grafo y
* se inicializan las funciones de construccion, destruccion, impresion y
* comparacion a ser empleadas por el tipo de datos manejado por el grafo
* @param constructor es la funcion empleada para inicializar elementos
* @param destructor es la funcion empleada para liberar elementos
* @param impresor es la funcion empleada para imprimir elementos
* @param comparador es la funcion empleada comparar elementos 
* @return res, estructura de datos del tipo grafo creado
*/
grafo newGrafo(void *(*constructor) (void *), void *(*destructor) (void *),
               void *(*impresor) (void *), int (*comparador) (void *,void *)) {
              
    grafo res = malloc(sizeof(struct _grafo));
    res -> cantidadVertices = 0;
    res -> cantidadArcos    = 0;
    
    res -> construirElem = constructor;
    res -> destruirElem  = destructor;
    res -> imprimirElem  = impresor;
    res -> compararElem  = comparador;
    return res;
      
}

/** 
* Destruccion de una estructura de tipo grafo. Se libera la memoria
* ocupada por dicha estructura
* @param g es el grado a ser liberado
*/
void freeGrafo(grafo g){
    free(g);
}


/******************************************************************************/
/**************************** MODULO PRUEBAS **********************************/
/******************************************************************************/


/**
* Creacion de un elemento tipo prueba. Se hace reserva de la memoria de la
* estructura prueba y se inicializa el mensaje que este porta
* @param mensaje es el mensaje que portara el elemento prueba
* @return mi_prueba, estructura de datos del tipo prueba creado
*/
void* newPrueba(void* mensaje) {
    
    char *right_message = (char*)mensaje;
    PRUEBA* mi_prueba = malloc(sizeof(PRUEBA));
    int tam_mensaje = strlen(right_message);
    char*   mensaje_prueba = malloc(tam_mensaje+1);
    strcpy(mensaje_prueba,right_message); 
    mi_prueba -> mi_mensaje = mensaje_prueba;
    
    return mi_prueba;
}

/** 
* Destruccion de una estructura de tipo prueba. Se libera la memoria
* ocupada por dicha estructura
* @param p es la prueba a ser liberada
*/
void* freePrueba(void *p){
   PRUEBA* mi_prueba = (PRUEBA*)p;
   free(mi_prueba->mi_mensaje);
   free(mi_prueba);
}

/**
* Representa una estructura de tipo prueba en forma de cadena
* de caracteres y la imprime en pantalla.
* @param p es la prueba a ser representada e impresa en pantalla
*/
void* print_prueba(void *p){
    PRUEBA* mi_prueba = (PRUEBA*)p;
    printf("Soy Prueba. Mi mensaje es: %s\n",mi_prueba->mi_mensaje);
}

/**
* Funcion de comparacion entre dos estructuras de tipo prueba.
* Retorna 1 si ysolo si ambas pruebas comparten exactamente el mismo mensaje
* @param p1 es la prueba a ser comparada con la prueba p2
* @param p2 es la prueba a ser comparada con la prueba p1
* @return 1, si las pruebas son identicas, 0 en caso contrario
*/
int compare_prueba(void *p1,void*p2){
    PRUEBA* prueba1 = (PRUEBA*)p1;
    PRUEBA* prueba2 = (PRUEBA*)p2;
    int pruebas_equivalentes;
    
    pruebas_equivalentes = strcmp(prueba1->mi_mensaje,prueba2->mi_mensaje);
    
    return pruebas_equivalentes==0;
}
