#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "node.h"


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
