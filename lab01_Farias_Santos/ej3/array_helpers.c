#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "array_helpers.h"

unsigned int array_from_file(int array[], unsigned int max_size, const char *filepath) {
    
    unsigned int size;
    
    FILE *file = fopen(filepath, "r"); //definimos file y con fopen le damos el valor de la direccion y le decimos que solo lea 

    fscanf(file, "%u", &size); //escaneamos el tamaño del array

    if (size > max_size){ //verificamos que el tamaño no supere el max_size
        printf("¡ERROR! El Tamaño es Superior al Permitido (100000)\n");
        fclose(file); //cerramos el file
        return 0u;
    }

    for (unsigned int i = 0; i < size; i++) //escanamos los elementos del array
    {
        fscanf(file, "%d", &array[i]);
    }
    
    printf("Datos Recolectados Correctamente\n"); //mostramos que los datos se guardaron con exito

    return size;
}

void array_dump(int a[], unsigned int length) { //imprimimos el array
    printf("[");
    for (unsigned int i = 0; i < length; i++) {
        if (i>0) {
            printf(",");
        }
        printf("%d", a[i]);
    }
    printf("]\n");
}
