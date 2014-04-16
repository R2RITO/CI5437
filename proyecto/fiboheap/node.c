#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "node.h"

/* FUNCION: make_node
 * DESC   : Crea un nuevo nodo
 * val    : Apuntador al valor del nodo
 * RETORNA: Un apuntador al nuevo nodo
 */
node make_node(void *val) {

    node newNode = malloc(sizeof(struct _node));
    newNode -> degree = 0;
    newNode -> parent = NULL;
    newNode -> child  = NULL;
    newNode -> left   = NULL;
    newNode -> right  = NULL;
    newNode -> mark   = 0;
    newNode -> key    = val;
    return newNode;
}


/* FUNCION: free_node
 * DESC   : Destruye un nodo
 * n      : Nodo a desturir
 */
void free_node(node n) {
    free(n);
}

/* FUNCION: free_node_cascade
 * DESC   : Destruye un nodo y sus familiares
 * n      : Nodo a destruir
 */
void free_node_cascade(node n) {
    // Recursivamente vamos a los hijos
    if (n->child != NULL) {
        free_node_cascade(n->child);
    }
    // Hacemos que el ultimo apunte a nulo
    (n->left)->right = NULL;
    // Vamos a eliminar a sus hermanos
    if (n->right != NULL) {
        free_node_cascade(n->right);
    }
    // Si ya no tiene ni hijos, ni mas hermanos, liberamos
    free(n);
}

