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
 * n      : Nodo a desturir
 */
void free_node(node n);


/* FUNCION: free_node_cascade
 * DESC   : Destruye un nodo y sus familiares
 * n      : Nodo a destruir
 */
void free_node_cascade(node n);
#endif
