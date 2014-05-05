#ifndef FILE_NODE
#define FILE_NODE

/* Forward declaration de nodo */
/* Para que no se queje el compilador */
typedef struct _node *node;

/* Estructura de un nodo */
typedef struct _node {
    node parent;
    node child;
    node left;
    node right;
    int  degree;
    int  mark;
    void *key;
} *node;

/* FUNCION: make_fib_node
 * DESC   : Crea un nuevo nodo
 * val    : Apuntador al valor del nodo
 * RETORNA: Un apuntador al nuevo nodo
 */
node make_fib_node(void *val);

/* FUNCION: free_node
 * DESC   : Destruye un nodo
 * f      : Funcion para liberar el valor del nodo
 * n      : Nodo a desturir
 */
void free_fib_node(node n, void (*f)(void *a));


/* FUNCION: free_fib_node_cascade
 * DESC   : Destruye un nodo y sus familiares
 * f      : Funcion para liberar el valor del nodo
 * n      : Nodo a destruir
 */
void free_fib_node_cascade(node n, void (*f)(void *a));
#endif
