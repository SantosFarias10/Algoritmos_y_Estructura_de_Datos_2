#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "pair.h"

pair_t pair_new(int x, int y){
    pair_t a;

    a.values[0] = x;
    a.values[1] = y;

    assert(a.values[0] == x && a.values[1] == y);

    return a;
}

int pair_first(pair_t p){
    assert(sizeof(p) == sizeof(pair_t));
    return p.values[0];
}

int pair_second(pair_t p) {
    assert(sizeof(p) == sizeof(pair_t));
    return p.values[1];
}

pair_t pair_swapped(pair_t p){
    assert(sizeof(p) == sizeof(pair_t));
    pair_t q = pair_new(p.values[1], p.values[0]);
    assert(pair_first(q) == pair_second(p) && pair_second(q) == pair_first(p));
    return q;
}

pair_t pair_destroy(pair_t p) {
    return p;
}