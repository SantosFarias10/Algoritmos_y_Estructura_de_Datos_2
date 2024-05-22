#include <stdio.h>
#include <stdlib.h>

#include "stack.h"

int main(){
    /*probando stack_empty | stack_to_array | stack_push*/
    stack s = stack_empty();
    stack_elem *array = stack_to_array(s);
    s = stack_push(s,1);

    /*Probando stack_size*/
    unsigned int tam = stack_size(s);
    printf("El tamaño de la pila es = %u\n\n", tam);

    /*probando stack_pop*/
    s = stack_pop(s);
    printf("Ejecutando stack_pop.....\n");
    tam = stack_size(s);
    printf("El nuevo valor de tamaño es = %u\n\n", tam);

    /*probando stack_push*/
    s = stack_push(s, 1);
    printf("Ejecutando stack_push....\n");
    tam = stack_size(s);
    printf("El nuevo valor de tamaño es = %u\n\n", tam);

    /*probando stack_to_array*/
    printf("El array devuelve NULL si    esta vacio??\n");
    if (array == NULL){
        printf("True\n");
    } else {
        printf("False\n");
    }

    for (unsigned int i = 2; i < 10; i++){
        s = stack_push(s,i);
    }

    tam = stack_size(s);
    printf("El nuevo valor de tamaño es = %u\n\n", tam);
    array = stack_to_array(s);
    printf("Array = ");
    printf("[");
    for (unsigned int i = 0u; i < tam; i++){
        printf("%u, ", array[i]);
    }
    printf("]\n\n");
    
    /*probando stack_is_empty*/
    if(stack_is_empty(s)){
        printf("True\n");
    } else {
        printf("False\n");
    }

    stack_destroy(s);
    free(array);

    return EXIT_SUCCESS;
}