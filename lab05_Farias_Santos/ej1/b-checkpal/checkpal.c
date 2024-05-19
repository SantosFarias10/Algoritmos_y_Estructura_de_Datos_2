#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "strfuncs.h"

#define MAX_LENGTH 33

#define SIZEOF_ARRAY(s) (sizeof(s) / sizeof(*s))

int main(void) {
    char user_input[MAX_LENGTH];
    char ignore_chars[] = {' ', '?', '!', ',', '-', '.'};
    char *filtered=NULL;

    printf("Ingrese un texto (no más de %d símbolos) para verificar palíndromo: ", MAX_LENGTH);

/*
 * char *fgets (char *string, int n, FILE *stream);
 
 * La función fgets() lee caracteres de la posición actual de ruta hasta el primer carácter de nueva línea (\n), hasta el final de la ruta o hasta que el número de caracteres leídos sea igual a n-1, lo que ocurra primero. La función fgets() almacena el resultado en serie y añade un carácter nulo (\0) al final de la serie. La serie incluye el carácter de nueva línea, si se lee. Si n es igual a 1, la serie está vacía.

 * fgets() devuelve un puntero al almacenamiento intermedio de serie si es satisfactorio. Un valor de retorno NULL indica un error o una condición de fin de archivo.
*/

    if (fgets(user_input, sizeof(user_input), stdin) == NULL) { /*fgets toma la variable donde guardamos la cadena de caracteres (user_input), la cantidad de caracteres que guardamos (sizeof(user_input) y stdin para poder leer lo que hay dentro del archivo*/
        printf("Error al leer la entrada.\n");
        return EXIT_FAILURE;
    }

    size_t tam = string_length(user_input);

    if (tam > 0 && user_input[tam-1] == '\n') {
        user_input[tam - 1] = '\0';
    }

    filtered = string_filter(user_input, ignore_chars[0]);
    for (unsigned int i=0; i < SIZEOF_ARRAY(ignore_chars); i++) {
        char *puntero = filtered;
        filtered = string_filter(filtered, ignore_chars[i]);
        free(puntero);
    }

    printf("El texto:\n\n"
            "\"%s\" \n\n"
            "%s un palíndromo.\n\n", user_input, string_is_symmetric(filtered) ? "Es": "NO es");

    free(filtered);

    return EXIT_SUCCESS;
}