#include <stdlib.h>
#include <assert.h>
#include "stack.h"
 
struct _s_stack {
    stack_elem elem;
    struct _s_stack *next;
    unsigned int tam;
};

stack stack_empty(){
    stack pila = NULL;
    return pila;
}

stack stack_push(stack s, stack_elem e){
    assert(s == NULL || s->tam == stack_size(s));
    stack pila = malloc(sizeof(struct _s_stack));

    pila->elem = e;
    pila->next = s;

    if (stack_is_empty(s)){
        pila->tam = 1u;
    } else {
        pila->tam = s->tam + 1u;
    }

    assert(pila->tam == stack_size(pila));    

    return pila;
}

stack stack_pop(stack s){ 
    assert(!stack_is_empty(s));
    assert(s->tam == stack_size(s));

    stack pila = s;
    s = s->next;
    if (!stack_is_empty(s)){
        s->tam = s->tam - 1;
    }
    free(pila);
    assert(s == NULL || s->tam == stack_size(s));
    return s;
}

unsigned int stack_size(stack s){
    if (stack_is_empty(s)){
        return 0u;
    }
    return s->tam;
}

stack_elem stack_top(stack s){
    assert(!stack_is_empty(s));
    return s->elem;    
}

bool stack_is_empty(stack s) {
    return (s == NULL);
}

stack_elem *stack_to_array(stack s){
    stack_elem *array;
    stack pila = s;
    unsigned int tam = stack_size(s);
    int n = tam - 1;

    if (tam == 0){
        array = NULL;
    } else {
        array = malloc(sizeof(stack_elem) * tam);
    }

    while (!stack_is_empty(pila)){
        array[n] = pila->elem;
        pila = pila->next;
        n--;
    }
    stack_destroy(pila);
    return array;
}

stack stack_destroy(stack s){
    stack pila = stack_empty();

    while (!stack_is_empty(pila)){
        pila = s;
        pila = pila->next;
        free(pila);
    }

    return pila;
}