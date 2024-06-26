#include <stdbool.h>
#include <stdlib.h>
#include <assert.h>

#include "counter.h"

struct _counter {
    unsigned int count;
};

counter counter_init(void) {
    counter c = malloc(sizeof(struct _counter)); /*guardamos un lugar de memoria para la estuctura _counter*/
    c->count = 0u; /*c apunta a count e inicilizamos en 0u (porque es un unsigned int)*/
    return c; 
}

void counter_inc(counter c) {
    c->count++;
}

bool counter_is_init(counter c) {
    return c->count == 0;
}

void counter_dec(counter c) {
    assert(!counter_is_init(c));
    c->count--;
}

counter counter_copy(counter c) {
    counter p = malloc(sizeof(struct _counter));
    p->count = c->count;
    return p;
}

void counter_destroy(counter c) {
    free(c);
    c = NULL;
}