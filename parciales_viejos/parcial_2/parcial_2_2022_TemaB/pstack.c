#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include "pstack.h"

struct s_pstack {
    unsigned int size;
    struct s_node *front;
};

struct s_node {
    pstack_elem elem;
    priority_t p;
    struct s_node *next;
};

static struct s_node * create_node(pstack_elem e, priority_t priority) {
    struct s_node *new_node = NULL;
    new_node = malloc(sizeof(struct s_node));
    assert(new_node!=NULL);
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

static bool invrep(pstack s) {
    unsigned int i = 0u;
    struct s_node *nodo = s->front;
    while (nodo != NULL) {
        nodo = nodo->next;
        i++;
    }
    return s->size == i;
}

pstack pstack_empty(void) {
    pstack s = NULL;
    s = malloc(sizeof(struct s_pstack));
    s->front = NULL;
    s->size = 0u;
    assert(pstack_is_empty(s));
    return s;
}

pstack pstack_push(pstack s, pstack_elem e, priority_t priority) {
    assert(invrep(s));
    struct s_node *new_node = create_node(e, priority);
    
    if (pstack_is_empty(s) || s->front->p <= priority) {
        new_node->next = s->front;
        s->front = new_node;
    } else {
        struct s_node *current = s->front;
        while (current->next != NULL && current->next->p > priority) {
            current = current->next;
        }
        new_node->next = current->next;
        current->next = new_node;
    }
    s->size++;
    assert(!pstack_is_empty(s));
    return s;
}

bool pstack_is_empty(pstack s) {
    return s->front == NULL && s->size == 0u;
}

pstack_elem pstack_top(pstack s) {
    assert(!pstack_is_empty(s));
    return s->front->elem;
}

priority_t pstack_top_priority(pstack s) {
    assert(!pstack_is_empty(s));
    return s->front->p;
}

unsigned int pstack_size(pstack s) {
    assert(invrep(s));
    return s->size;
}

pstack pstack_pop(pstack s) {
    assert(!pstack_is_empty(s));
    struct s_node *killme = s->front;
    s->front = s->front->next;
    s->size--;
    killme = destroy_node(killme);
    return s;
}

pstack pstack_destroy(pstack s) {
    assert(invrep(s));
    while (s->front != NULL) {
        s = pstack_pop(s);
    }
    free(s);
    s = NULL;
    assert(s == NULL);
    return s;
}
