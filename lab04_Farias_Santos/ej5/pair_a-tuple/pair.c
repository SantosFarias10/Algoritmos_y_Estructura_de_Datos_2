#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "pair.h"

pair_t pair_new(int x, int y){

    pair_t p;

    p.fst = x;
    p.snd = y;

    assert(p.fst == x && p.snd == y);

    return p;
}

int pair_first(pair_t p){
    /*¿Caul seria la pre/postCondicion?*/
    return p.fst;
}

int pair_second(pair_t p){
    /*¿Caul seria la pre/postCondicion?*/
    return p.snd;
}

pair_t pair_swapped(pair_t p){
    /*¿PreCondicion?*/
    pair_t q;
    q = pair_new(p.snd, p.fst); /*definimos un nuevo pair pero con los valores cambiados*/
    assert(pair_first(q) == pair_second(p) && pair_second(q) == pair_first(p));
    return q;
}

pair_t pair_destroy(pair_t p){
    return p;
}