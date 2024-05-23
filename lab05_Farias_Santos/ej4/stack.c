#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#include "stack.h"
 
struct _s_stack {
    stack_elem elem;
    struct _s_stack *next;
    unsigned int size;
};

stack stack_empty(void) {
    stack s = NULL;

    return s;
}

stack stack_push(stack s, stack_elem e) {
    stack pila = malloc(sizeof(struct _s_stack)); /*cramos una nueva pila*/

    pila->elem = e; /*le agregamos el elemento e*/
    pila->next = s; /*y luego le decimos que el siguiente apunte a la pila original*/

    pila->size = stack_size(s) + 1u; /*sumamos 1 a size*/

    return pila;
}

stack stack_pop(stack s) {
    stack pila = s;
    s = s->next;

    free(pila); /*eliminamos el elemento tope de la pila*/
    
    return s;
}

unsigned int stack_size(stack s) {
    if (stack_is_empty(s)) { /*si es vacio retornamos 0*/
        return 0u;
    }

    return s->size;
}

stack_elem stack_top(stack s) {
    /*PRE: que la pila no sea vacia*/
    assert(!stack_is_empty(s));
    return s->elem; /*retornamos el elemento que este en el tope siempre y cuando la pila no sea vacia*/
}

bool stack_is_empty(stack s) {
    return (s == NULL);
}

stack_elem *stack_to_array(stack s) {
    stack_elem *array = NULL; /*creamos un nuevo array para guardar los elementos*/
    stack pila = s; /*una pila auxiliar*/

    if (!stack_is_empty(s)) {
        /*
         * La función calloc() reserva espacio de almacenamiento para una matriz de elementos num, cada uno de ellos de longitud tamaño bytes. La función calloc() proporciona a todos los bits de cada elemento un valor inicial de 0.
         * La función calloc() devuelve un puntero al espacio reservado. El espacio de almacenamiento al que apunta el valor de retorno está adecuadamente alineado para el almacenamiento de cualquier tipo de objeto. 
         * El valor de retorno es NULL si no hay suficiente almacenamiento, o si núm o tamaño es 0.
        */
        array = calloc(stack_size(s), sizeof(stack_elem)); /*abrimos un espacio de memoria e inicializamos*/
        
        /*guardamos los elementos en array (empezando de atras para adelante si no se imprime al reves la torre xd)*/
        for (unsigned int i = stack_size(s); i > 0u; --i) {
            array[i - 1u] = pila->elem;
            pila = pila->next;
        }
    }

    return array;
}

stack stack_destroy(stack s) {
    stack pila = s;
    
    while (!stack_is_empty(pila)) { /*mientras pila no sea vacia vamos quitandole el tope*/
        pila = stack_pop(pila);
    }

    return NULL;
}