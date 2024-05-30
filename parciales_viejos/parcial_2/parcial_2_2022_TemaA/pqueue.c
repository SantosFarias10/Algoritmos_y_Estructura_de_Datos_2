#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include "pqueue.h"

struct s_pqueue {
    unsigned int size;
    struct s_node *first;
    //struct s_node *last; //Sirve??
};

struct s_node {
    pqueue_elem elem;
    unsigned int p;        //Prioridad
    struct s_node *next;
};

static struct s_node * create_node(pqueue_elem e, unsigned int priority) {
    struct s_node *new_node = NULL;
    new_node = malloc(sizeof(struct s_node));
    assert(new_node != NULL);
    new_node->elem = e;
    new_node->p = priority;
    new_node->next = NULL;
    return new_node;
}

static struct s_node * destroy_node(struct s_node *node) {
    assert(node != NULL);
    node->next = NULL;
    free(node);
    node = NULL;
    assert(node == NULL);
    return node;
}

static bool invrep(pqueue q) {
    unsigned int i = 0u;
    struct s_node *nodo = q->first;
        while (nodo != NULL) {
            nodo = nodo->next;
            i++;
        }
    return q->size == i;
}

pqueue pqueue_empty(void) {
    pqueue q = NULL;
    q = malloc(sizeof(struct s_pqueue));
    q->size = 0u;
    q->first = NULL;
    return q;
}

pqueue pqueue_enqueue(pqueue q, pqueue_elem e, unsigned int priority) {
    assert(invrep(q));
    struct s_node *new_node = create_node(e, priority);
    
    if (pqueue_is_empty(q) || q->first->p > priority) {
        new_node->next = q->first;
        q->first = new_node;
    } else {
        struct s_node *current = q->first;
        while (current->next != NULL && current->next->p <= priority) {
            current = current->next;
        }
        new_node->next = current->next;
        current->next = new_node;
    }
    q->size++;
    return q;
}

bool pqueue_is_empty(pqueue q) {
    return q->first == NULL && q->size == 0u;
}

pqueue_elem pqueue_peek(pqueue q) {
    assert(!pqueue_is_empty(q));
    return q->first->elem;
}

unsigned int pqueue_peek_priority(pqueue q) {
    assert(!pqueue_is_empty(q));
    return q->first->p;
}

unsigned int pqueue_size(pqueue q) {
    assert(invrep(q));
    return q->size;
}

pqueue pqueue_dequeue(pqueue q) {
    struct s_node *killme = q->first;
    q->first = q->first->next;
    killme = destroy_node(killme);
    q->size--;
    return q;
}

pqueue pqueue_destroy(pqueue q) {
    assert(invrep(q));
    while (q->first != NULL) {
        q = pqueue_dequeue(q);
    }
    free(q);
    q = NULL;
    assert(q == NULL);
    return q;
}
