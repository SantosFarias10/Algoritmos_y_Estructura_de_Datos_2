#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include "pqueue.h"

struct s_pqueue {
    struct s_node **array; //** explicado al fondo
    unsigned int size;
    priority_t min_p;
};

struct s_node {
    pqueue_elem elem;
    struct s_node *next;
};

static struct s_node * create_node(pqueue_elem e) {
    struct s_node* new_node = malloc(sizeof(struct s_node));
    assert(new_node != NULL);
    new_node->elem = e;
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
    return q != NULL && q->array != NULL;
}

pqueue pqueue_empty(priority_t min_priority) {
    pqueue q = malloc(sizeof(struct s_pqueue));
    q->array = calloc(min_priority + 1, sizeof(struct s_node *));
    q->min_p = min_priority;
    q->size = 0u;
    assert(invrep(q) && pqueue_is_empty(q));
    return q;
}

pqueue pqueue_enqueue(pqueue q, pqueue_elem e, priority_t priority) {
    assert(invrep(q) && priority <= q->min_p);
    struct s_node *new_node = create_node(e);

    if (q->array[priority] == NULL) {
        q->array[priority] = new_node;
    } else if (q->array[priority] != NULL) {
        struct s_node *current = q->array[priority];
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = new_node;
    }
    q->size++;
    assert(invrep(q));
    return q;
}

bool pqueue_is_empty(pqueue q) {
    assert(invrep(q));
    return q->size == 0u;
}

pqueue_elem pqueue_peek(pqueue q) {
    assert(invrep(q) && !pqueue_is_empty(q));
    return q->array[pqueue_peek_priority(q)]->elem;
}

priority_t pqueue_peek_priority(pqueue q) {
    assert(invrep(q) && !pqueue_is_empty(q));
    unsigned int max_p = 0u;
    for (unsigned int i = q->min_p; i != 0u; i--) {
        if (q->array[i] != NULL) {
            max_p = i;
        }
    }
    return max_p;
}

size_t pqueue_size(pqueue q) {
    assert(invrep(q));
    return q->size;
}

pqueue pqueue_dequeue(pqueue q) {
    assert(invrep(q) && !pqueue_is_empty(q));
    struct s_node *killme = q->array[pqueue_peek_priority(q)];
    q->array[pqueue_peek_priority(q)] = q->array[pqueue_peek_priority(q)]->next;
    destroy_node(killme);
    q->size--;
    assert(invrep(q));
    return q;
}

pqueue pqueue_destroy(pqueue q) {
    assert(invrep(q));
    while (!pqueue_is_empty(q)) {
        q = pqueue_dequeue(q);
    }
    free(q->array);
    q->array = NULL;
    free(q);
    q = NULL;
    return q;
}

/* Un puntero a puntero, como struct s_node **, es una variable que contiene la dirección de memoria de otro puntero. Esto es útil cuando necesitas manejar dinámicamente un array de punteros. En el caso de struct s_node **array, cada elemento de array es un puntero a un struct s_node. */