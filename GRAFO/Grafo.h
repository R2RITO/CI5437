/**
* @file
* @author  Arturo Voltattorni, Fernando D'agostino & Oswaldo Jimenez 
*
* @section Descripcion
*
* Definicion y prototipos del Tipo abstracto de datos Grafo.
*/

#ifndef FILE_GRAFO
#define FILE_GRAFO

#include "Nodo.h"
#include "Arco.h"


/** 
* Estructura de un Grafo, compuesto por numero de vertices, arcos
*/
typedef struct _grafo {
    
    /** numero de vertices adlojados en el grafo*/
    int cantidadVertices;
    
    /** numero de arcos alojados en el grafo*/
    int cantidadArcos;
    
     /** Funcion de inicializacion de la estructura que alojara el grafo*/
    void *(*construirElem) (void *);
    
     /** Funcion de liberacion de la estructura que alojara el grafo*/
    void *(*destruirElem) (void *);
    
    /** Funcion de impresion de la estructura que alojara el grafo*/
    void *(*imprimirElem) (void *);
    
    /** Funcion de comparacion de la estructura que alojara el grafo*/
    int (*compararElem) (void *,void *);
    
} *grafo;


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
               void *(*impresor) (void *), int (*comparador) (void *,void *));

/** 
* Destruccion de una estructura de tipo grafo. Se libera la memoria
* ocupada por dicha estructura
* @param g es el grado a ser liberado
*/
void freeGrafo(grafo g);

/******************************************************************************/
/**************************** MODULO PRUEBAS **********************************/
/******************************************************************************/

/** 
* Estructura de una Prueba, compuesta por un mensaje portador
*/
typedef struct prueba {
        /**Mensaje que identifica y porta la prueba*/
        char* mi_mensaje;
} PRUEBA;

/**
* Creacion de un elemento tipo prueba. Se hace reserva de la memoria de la
* estructura prueba y se inicializa el mensaje que este porta
* @param mensaje es el mensaje que portara el elemento prueba
* @return mi_prueba, estructura de datos del tipo prueba creado
*/
void* newPrueba(void* mensaje);

/** 
* Destruccion de una estructura de tipo prueba. Se libera la memoria
* ocupada por dicha estructura
* @param p es la prueba a ser liberada
*/
void* freePrueba(void *p);

/**
* Representa una estructura de tipo prueba en forma de cadena
* de caracteres y la imprime en pantalla.
* @param p es la prueba a ser representada e impresa en pantalla
*/
void* print_prueba(void *p);

/**
* Funcion de comparacion entre dos estructuras de tipo prueba.
* Retorna 1 si ysolo si ambas pruebas comparten exactamente el mismo mensaje
* @param p1 es la prueba a ser comparada con la prueba p2
* @param p2 es la prueba a ser comparada con la prueba p1
* @return 1, si las pruebas son identicas, 0 en caso contrario
*/
int compare_prueba(void *p1,void*p2);

#endif

