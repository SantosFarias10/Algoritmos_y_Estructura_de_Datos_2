#include <stdlib.h>
#include <assert.h>
#include "stack.h"

struct _s_stack {
    stack_elem *elems;      // Arreglo de elementos
    unsigned int size;      // Cantidad de elementos en la pila
    unsigned int capacity;  // Capacidad actual del arreglo elems
};

/*

 * La función realloc() cambia el tamaño de un bloque de almacenamiento reservado anteriormente. Toma como argumentos un puntero 
 que apunta al principio del bloque y el tamaño que proporciona el nuevo tamaño del bloque (en bytes)
 * Si el tamaño = 0, y el puntero no es NULL => la llamada es equivalente a free(puntero). 
 * Si el puntero = NULL => la llamada es equivalente a malloc(tamaño).

*/

stack stack_empty(){
    stack pila = malloc(sizeof(struct _s_stack)); /*definimos una pila y reservamos un espacio de almacenamiento*/

    pila->elems = NULL; /*inicializamos el punter*/
    pila->size = 0u; /*inicializamos el tamaño*/
    pila->capacity = 0u; /*inicializamos la capacidad*/

    return pila;
}

stack stack_push(stack s, stack_elem e){
    
    if (s->elems == NULL){ /*si la pila aun no tiene elementos y no ha sido asignada memoria =>*/
        s->capacity = 1u; /*inicilizamos la capacidad a 1*/
        s->elems = malloc(sizeof(stack_elem)); /*le asignamos memoria para un solo elemento*/
    } 
    else if (s->size >= s->capacity){ /*si la pila ya tiene elementos y ya esta llena, osea que el tamaño es igual o supera la capacidad maxima => duplicamos la memoria*/
        s->capacity = s->capacity * 2u;
        s->elems = realloc(s->elems, sizeof(stack_elem) * s->capacity); /*=> con realloc asignamos + memoria para los elementos, duplicando la capacidad*/
    }

    /*finalmente agregamos el elemento*//*finalmente agregamos el elemento*/
    s->elems[s->size] = e; 
    /*y sumamos 1 a size*/
    s->size = s->size + 1u; 

    return s;
}

stack stack_pop(stack s){
    /*PRE: que no sea vacia la pila*/
    assert(!stack_is_empty(s)); 

    /*le restamos 1 a size*/
    s->size--; 

    return s;
}

unsigned int stack_size(stack s){
    return s->size;
}

stack_elem stack_top(stack s){
    /*PRE: que no sea vacia la pila*/
    assert(!stack_is_empty(s)); 

    /*retornamos el ultimo elemento que se añadio a la pila (le restamos 1 ya que empezamos a contar desde el 0)*/
    return s->elems[s->size-1u]; 
}

bool stack_is_empty(stack s){
    return s->size == 0;
}

stack_elem *stack_to_array(stack s){
    if (stack_size(s) == 0){ /*verificamos que la pila no este vacia*/
        return NULL; /*y si lo es retornamos NULL*/
    } 

    /*creamos un nuevo puntero donde vamos a almacenar todos los elementos*/
    stack_elem *array = malloc(sizeof(stack_elem) * s->size); 
    
    /*verificamos que no haya un error en la asignacion*/
    if (array == NULL){ 
        return NULL;
    }
    
    /*copiamos los elementos de la pila en el nuevo arreglo */
    for (unsigned int i = 0; i < s->size; i++){ 
        array[i] = s->elems[i];
    }
    
    return array;    
}

stack stack_destroy(stack s){
    free(s->elems); /*liberamos la memoria del arreglo de elementos*/
    free(s); /*liberamos la memoria de la*/
    
    return NULL;
}