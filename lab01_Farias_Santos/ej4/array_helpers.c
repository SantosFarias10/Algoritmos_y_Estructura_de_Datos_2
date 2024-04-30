#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "array_helpers.h"

unsigned int array_from_file(int array[], unsigned int max_size, const char *filepath) {
    unsigned size;

    FILE *file = fopen(filepath, "r"); /*Definimos el file y con la funcion fopen le damos como argumento el filepath (la direccion del archivo) y como segundo argumento le pedimos que solo lea lo que contiene esa direccion*/

    fscanf(file, "%u", &size); /*con la funcion fscanf escaneamos el tamaño del array de la direccion*/

    if (size > max_size){ /*si el tamaño escaneado es superior al perimitido (100000) entonces imprimimos un mensaje de error, cerramos el file y returnamos un unsigned 0*/
        printf("¡¡¡ERROR!!! El tamaño es superior al permitido\n");
        fclose(file);
        return 0u;
    }

    for (unsigned int i = 0; i < size; i++){ /*con el for vamos escaneando cada elemento del array con la funcion fscanf que esta en la direccion*/
        fscanf(file, "%d", array[i]);
    }
    
    printf("Datos Recolectados Correctamente\n"); /*imprimimos un mensaje para verificar que hallamos leido bien cada elemento de la direccion*/

    return size;
}

void array_dump(int a[], unsigned int length) { /*imprimimos el array*/
    printf("[");
    for (unsigned int i = 0; i < length; i++){
        if (i>0){
            printf(", ");
        }
        printf("%d", a[i]);
    }
    printf("]");
}

bool array_is_sorted(int a[], unsigned int length){
    bool res = true;
    for (unsigned int i = 0; i < length-1; i++){
        if (a[i] <= a[i+1]){
            res = true;
        } else {
            res = false;
        }
    }

    return res;
}