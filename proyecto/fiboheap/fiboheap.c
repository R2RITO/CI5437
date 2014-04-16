#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <math.h>
#include "fiboheap.h"

fiboheap make_fib_heap(int (*c)(void *a, void *b)) {
    // Reservamos espacio para el fiboheap
    fiboheap fibo = malloc(sizeof(struct _fiboheap));
    // Seteamos los valores
    fibo->size = 0;
    fibo->min  = NULL;
    fibo->compare = c;
    return fibo;
}


void fib_heap_insert(fiboheap f, void *val) {

    node x = make_node(val);

    if (f->min == NULL) {
        // A la derecha el mismo
        x->right = x;
        // A la izquierda el mismo
        x->left  = x;
        // El minimo es el mismo, no hay mas nadie
        f->min   = x;        
    } else {
        // A la derecha del nuevo, el minimo
        x->right = f->min;
        // A la izquierda, el izquierdo del minimo
        x->left  = (f->min)->left;
        // A la derecha del anterior al minimo, el nuevo
        ((f->min)->left)->right = x;
        // A la izquierda del minimo, el nuevo
        (f->min)->left = x;
    
        if (f->compare(x->key, (f->min)->key) < 0) {
            // Actualizamos el minimo
            f->min = x;
        }
    }
    // Aumentamos el numero de nodos
    f->size = (f->size) + 1;
}


void concatenate(node a, node b) {

    // En caso de que alguno sea null, retornar
    if ((a == NULL)||(b == NULL)) {
        return;
    }

    // Concatenamos ambas listas circulares
    // Obtenemos los hermanos de cada uno
    node rightMinA = a->right;
    node leftMinB  = b->left;
    // Hacemos que los minimos se referencien entre si
    a->right = b;
    b->left  = a;
    // Hacemos que los hermanos se referencien entre si
    rightMinA->left = leftMinB;
    leftMinB->right  = rightMinA;
}

fiboheap fib_heap_union(fiboheap a, fiboheap b) {

    fiboheap h = make_fib_heap(a->compare);

    // Si el primer fiboheap esta vacio
    if (a->min == NULL) {
        h->min = b->min;
        h->size = b->size;
        return h;
    }

    // Si el segundo fiboheap esta vacio
    if (b->min == NULL) {
        h->min = a->min;
        h->size = a->size;
        return h;
    }

    // Concatenamos ambas listas circulares
    concatenate((a->min),(b->min));

    // Actualizamos el minimo del nuevo heap
    if (h->compare((b->min)->key,(a->min)->key) < 0) {
        h->min = b->min;
    } else {
        h->min = a->min;
    }
    // Actualizamos el tamano del nuevo heap
    h->size = a->size + b->size;
    return h;
}


int redondear(double f) {
    double res;
    modf(f,&res);
    return (int) res; 
}


void fib_heap_link(fiboheap f, node y, node x) {

    // Quitamos al nodo y de la lista de raices
    node prev = y->left;
    node next = y->right;
    prev->right = next;
    next->left  = prev;
    // Hacemos que y sea hijo de x
    y->parent = x;
    // Aislamos a y en una lista 'nueva'
    y->right  = y;
    y->left   = y;
    // Verificamos si x tenia hijos
    if (x->child != NULL) {
        // Tenia hijos antes debemos enlazarlos
        concatenate(y, x->child);
    }
    // Notese que si no tenia hijos queda bien formada la lista circular

    // El nuevo hijo de x sera y
    x->child = y;

    // Cambiamos la marca de y
    y->mark = 0;
}

int contarRaices(fiboheap f) {
    int res = 0;
    node actual = f->min;
    if (actual != NULL) {
        res++;
        actual = actual->right; 
        while (actual != f->min) {
            actual = actual->right;
            res++;
        }
    }
    return res;
}

void consolidate(fiboheap f) {
    
    // Calculamos el tamano del arreglo auxiliar
    double tamAdouble = log((double) (f->size))/log((1+sqrt(5))/2);
    int tamA = redondear(tamAdouble);
    // Creamos el arreglo auxiliar
    node A[tamA+1];
    // Escribimos null en todas las casillas
    int i;
    for (i=0; i<=tamA; i++) {
        A[i] = NULL;
    }
    // Nos paramos en el minimo, vamos a recorrer la lista de
    // raices que tenemos
    node actual = f->min;
    // Para no perder el nodo actual de la iteracion
    node x;
    // Variable para almacenar el apuntador al nodo previo en
    // una casilla del arreglo
    node y;
    // Variable auxiliar para intercambiar apuntadores si es
    // necesario
    node aux;
    // Para almacenar el grado de un nodo que estemos trabajando
    int degree;

    // MEJORAR ESTO!!!
    int numRaices = contarRaices(f);
    node raices[numRaices];
    node raiz = (f->min)->right;
    raices[0] = f->min;
    i = 1;
    while (raiz != f->min) {
        raices[i] = raiz;
        raiz = raiz->right;
        i++;
    }

    // Para todos las raices en el fiboheap:
    for (i=0; i<numRaices; i++) {
        // Para no perder la iteracion
        x = raices[i];
        // Obtenemos el grado de dicha raiz
        degree = x->degree;
        // Si ya habia un arbol en la casilla del arreglo
        while (A[degree] != NULL) {
            // Guardamos el apuntador al anterior
            y = A[degree];
            // Comparamos
            if (f->compare(x->key, y->key) > 0) {
                aux = x;
                x = y;
                y = aux;
            }
            fib_heap_link(f,y,x); // AQUI VA FIB_HEAP_LINK(A,y,x)
            A[degree] = NULL;
            degree++;
        }
        A[degree] = x;
    }

    f->min = NULL;

    // Procedemos a concatenar las raices:
    for (i=0; i<=tamA; i++) {
        // Si la casilla no esta vacia
        if (A[i] != NULL) {
            // Si aun no hay minimo
            if (f->min == NULL) {
                // El minimo sera por los momentos A[i]
                f->min = A[i];
                // Lo aislamos de los demas poniendolo a el solo
                // en una lista de raices 'nueva'
                A[i]->right = A[i];
                A[i]->left  = A[i];
            } else {
                // Tenemos que insertarlo en la lista de raices
                // Lo aislamos en una lista de raices 'nueva'
                A[i]->right = A[i];
                A[i]->left  = A[i];
                // Concatenamos ambas listas circulares
                concatenate(f->min,A[i]);
                // Actualizamos el minimo
                if (f->compare(A[i]->key, (f->min)->key) < 0) {
                    f->min = A[i];
                }
            }
        }
    }
}


node fib_heap_extract_min(fiboheap f) {

    node z = f->min;
    if (z != NULL) {
        // Si el minimo tiene hijos
        if (z->child != NULL) {
            // Obtenemos el primer hijo del minimo
            node zChild = z->child;
            // Tomamos los hijos del minimo y los colocamos en
            // la lista de nodos raices
            concatenate(z, zChild); 
            // Le colocamos NULL como padre al primer hijo del minimo
            zChild->parent = NULL;
            // Hacemos lo mismo para el resto de los hijos del minimo
            node sibling = zChild->right;
            while (zChild != sibling) {
                sibling->parent = NULL;
                sibling = sibling->right;
            }
        }
        // Eliminamos al minimo de la lista de raices
        node prev = z->left;
        node next = z->right;
        prev->right = next;
        next->left  = prev;

        // Verificamos si z estaba solo
        if (z == z->right) {
            f->min = NULL;
        } else {
        // Si no estaba solo entonces
            f->min = z->right;
            consolidate(f);
        }
        // Decrementamos el numero de nodos
        f->size = (f->size)-1;
    }
    return z;
}
