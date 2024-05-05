#include <stdlib.h>  /* EXIT_SUCCESS... */
#include <stdio.h>   /* printf()...     */
#include "pair.h"    /* TAD Par         */

static
void show_pair(pair_t p) {
    printf("(%d, %d)\n", pair_first(p), pair_second(p));
}

int main(void) {
    pair_t p, q;
    // Nuevo par p
    p = pair_new(3, 4);
    // Se muestra el par por pantalla
    printf("p = ");
    show_pair(p);
    // Nuevo para q con elementos de p intercambiados
    q = pair_swapped(p);
    // Se muestra q
    printf("q = ");
    show_pair(q);
    // Se destruyen p y q
    p = pair_destroy(p);
    q = pair_destroy(q);
    return EXIT_SUCCESS;
}

/*La diferencia entra la especificacion del ejercicio anterior y esta, es que en esta es mas abstracta, ya que en vez de implementar con el tipo INT, se usa un nuevo tipo que es enum*/