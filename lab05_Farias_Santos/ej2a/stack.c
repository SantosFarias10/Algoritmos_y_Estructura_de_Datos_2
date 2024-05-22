#include <stdlib.h>
#include <assert.h>
#include "stack.h"
 
struct _s_stack {
    stack_elem elem;
    struct _s_stack *next;
};

stack stack_empty(){
    stack pila = NULL;
    return pila;
}

stack stack_push(stack s, stack_elem e){
    stack pila = malloc(sizeof(struct _s_stack));

    pila->elem = e;
    pila->next = s;

    return pila;
}

stack stack_pop(stack s){ /*verficar si esta bien*/
    if (!stack_is_empty(s)){
        stack pila = s;
        s = s->next;
        free(pila);
    }
    return s;
}

unsigned int stack_size(stack s){
    unsigned int n = 0u;
    stack pila = s;

    while (!stack_is_empty(pila)){
        pila = pila->next;
        n++;
    }

    return n;
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
    int n = stack_size(s);
    unsigned int tam = n;

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