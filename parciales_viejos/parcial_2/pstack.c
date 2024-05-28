#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include "pstack.h"

struct s_pstack {
    struct s_node *tope;
    unsigned int size;
};

struct s_node {
    pstack_elem elem;
    priority_t priority;
    struct s_node *next;
};

static struct s_node * create_node(pstack_elem e, priority_t priority) {

    struct s_node *new_node = NULL; /*Creamos un nuevo nodo*/
    new_node = malloc(sizeof(struct s_node)); /*Reservamos espacio en la memoria*/

    assert(new_node!=NULL); /*verificamos que sea distinto de null*/

    new_node->elem = e; 
    new_node->priority = priority;
    new_node->next = NULL;

    return new_node;
}

static struct s_node * destroy_node(struct s_node *node) {
    assert(node != NULL);

    free(node); /*liberamos la memoria*/

    node = NULL;

    assert(node == NULL);
    return node;
}

static bool invrep(pstack s) {
    return s != NULL;
}

pstack pstack_empty(void) {

    pstack s=NULL; /*definimos un pstack*/
    s = malloc(sizeof(struct s_pstack));/*Reservamos un lugar en la memoria*/

    /*inicializamos*/
    s->tope = NULL; 
    s->size = 0u;

    return s; /*retornamos la pstack*/
}

pstack pstack_push(pstack s, pstack_elem e, priority_t priority) {
    assert(invrep(s)); /*verificamos el invariante*/

    struct s_node *new_node = create_node(e, priority); /*creamos un nuevo nodo*/

    if (s->tope == NULL || s->tope->priority < priority){
        new_node->next = s->tope;
        s->tope = new_node;
    } else {
        struct s_node *aux = s->tope;
        while((aux->next !=NULL) && (aux->next->priority >= priority)){
            aux = aux->next;
        }
        new_node->next = aux->next;
        aux->next = new_node;
    }

    s->size += 1u;
    return s;
}

bool pstack_is_empty(pstack s) {
    assert(invrep(s));

    return ((s->tope == NULL) && (s->size == 0u)); /*Verificar*/
}

pstack_elem pstack_top(pstack s) {
    assert(!pstack_is_empty(s));
    return s->tope->elem;
}

priority_t pstack_top_priority(pstack s) {
    assert(!pstack_is_empty(s));
    return s->tope->priority;
}

unsigned int pstack_size(pstack s) {
    assert(invrep(s));
    unsigned int size = s->size;
    return size;
}

pstack pstack_pop(pstack s) {
    assert(!pstack_is_empty(s));
    struct s_node *aux = s->tope;
    s->tope = s->tope->next;
    free(aux);
    s->size--;
    return s;
}

pstack pstack_destroy(pstack s) {
    assert(invrep(s));

    struct s_node *node = s->tope;
    while (node != NULL){
        struct s_node *killme=node;
        node = node->next;
        killme = destroy_node(killme);    
    }

    free(s);
    s = NULL;
    assert(s == NULL);
    return s;
}