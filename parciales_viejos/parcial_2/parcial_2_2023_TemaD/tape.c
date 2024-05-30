#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <assert.h>
#include "tape.h"

struct _s_node {
    tape_elem elem;
    struct _s_node *next;
};

typedef struct _s_node * node_t;

struct _s_tape {
    unsigned int size;
    node_t cursor;  // Puntero al elemento actual
    node_t start;   // Puntero al primer nodo de la cinta
};

static bool invrep(tape_t tape) {
    unsigned int i = 0u;
    node_t nodo = tape->start;
    while (nodo != NULL) {
        nodo = nodo->next;
        i++;
    }
    return tape->size == i;
}

static node_t create_node(tape_elem e) {
    node_t node = malloc(sizeof(struct _s_node));
    node->elem = e;
    node->next = NULL;
    return node;
}

static node_t destroy_node(node_t node) {
    free(node);
    return NULL;
}

tape_t tape_create(void) {
    tape_t tape = NULL;
    tape = malloc(sizeof(struct _s_tape));
    tape->cursor = NULL;
    tape->start = NULL;
    tape->size = 0u;
    assert(invrep(tape) && tape_is_empty(tape) && tape_at_start(tape));
    return tape;
}

tape_t tape_rewind(tape_t tape) {
    tape->cursor = tape->start;
    return tape;
}


bool tape_at_start(tape_t tape) {
    return tape->cursor == tape->start;
}

bool tape_at_stop(tape_t tape) {
    return tape->cursor == NULL;
}

bool tape_is_empty(tape_t tape) {
    return tape->size == 0u;
}

unsigned int tape_length(tape_t tape) {
    return tape->size;
}

tape_t tape_step(tape_t tape) {
    assert(!tape_is_empty(tape));
    tape->cursor = tape->cursor->next;
    return tape;
}

tape_t tape_insertl(tape_t tape, tape_elem e) {
    assert(invrep(tape));
    node_t new_node = create_node(e);
    if (tape->start == tape->cursor) {
        new_node->next = tape->start;
        tape->start = new_node;
        tape->cursor = new_node;
    } else {
        node_t anterior = tape->start;
        while (anterior->next != tape->cursor) {
            anterior = anterior->next;
        }
        anterior->next = new_node;
        new_node->next = tape->cursor;
        tape->cursor = new_node;
    }
    tape->size++;
    assert(invrep(tape) && !tape_is_empty(tape) && !tape_at_stop(tape) && e == tape_read(tape));
    return tape;
}

tape_t tape_insertr(tape_t tape, tape_elem e) {
    assert(invrep(tape) && (!tape_at_stop(tape) || tape_is_empty(tape)));
    node_t new_node = create_node(e);
    if (tape->start != NULL) {
        new_node->next = tape->cursor->next;
        tape->cursor->next = new_node;
        tape->cursor = new_node;
    } else {
        tape->start = new_node;
        tape->cursor = new_node;
    }
    tape->size++;
    assert(invrep(tape) && !tape_is_empty(tape) && !tape_at_stop(tape) && e == tape_read(tape));
    return tape;
}

tape_t tape_erase(tape_t tape) {
    assert(!tape_at_stop(tape));
    node_t node_to_erase = tape->cursor;

    if (tape->cursor == tape->start) {
        tape->start = tape->cursor->next;
        tape->cursor = tape->start;
    } else {
        node_t anterior = tape->start;
        while (anterior->next != tape->cursor) {
            anterior = anterior->next;
        }
        anterior->next = tape->cursor->next;
        tape->cursor = anterior->next;
    }
    destroy_node(node_to_erase);
    tape->size--;
    assert(invrep(tape));
    return tape;
}

tape_elem tape_read(tape_t tape) {
    assert(tape->cursor != NULL);
    return tape->cursor->elem;
}

void tape_dump(tape_t tape) {
    assert(invrep(tape));
    node_t node=tape->start;
    printf("#");
    while (node != NULL) {
        if (node != tape->cursor) {
            printf("-%c-", node->elem);
        } else {
            printf("-[%c]-", node->elem);
        }
        node = node->next;
    }
    if (tape->cursor==NULL) {
        printf("-[]-");
    }
    printf("#\n");
}

tape_t tape_copy(tape_t tape) {
    tape_t tape_c = tape_create();
    tape = tape_rewind(tape);
    while (!tape_at_stop(tape)) {
        tape_c = tape_insertr(tape_c, tape->cursor->elem);
        tape = tape_step(tape);
    }
    invrep(tape_c);
    return tape_c;
}

tape_t tape_destroy(tape_t tape) {
    tape = tape_rewind(tape);
    while (!tape_is_empty(tape)) {
        tape = tape_erase(tape);
    }
    free(tape);
    return NULL;
}
