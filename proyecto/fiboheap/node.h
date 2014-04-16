#ifndef FILE_NODE
#define FILE_NODE

typedef struct _node *node;

typedef struct _node {
    node parent;
    node child;
    node left;
    node right;
    int  degree;
    int  mark;
    void *key;
} *node;


node make_node(void *val);


#endif
