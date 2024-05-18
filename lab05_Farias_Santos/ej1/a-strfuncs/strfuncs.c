#include <stdio.h>
#include <stdlib.h>

#include "strfuncs.h"

size_t string_length(const char *str){
    size_t tam = 0;

    while (str[tam] != '\0'){
        tam = tam + 1;
    }

    return tam;
}

char *string_filter(const char *str, char c){
    size_t tam = string_length(str);
    size_t i = 0;
    size_t j = 0;
    char *str_puntero = malloc(sizeof(char) * tam);

    if (str_puntero == NULL){
        return NULL;
    }

    while (i < tam){
        if  (str[i] != c){
            str_puntero[j] = str[i];
            j++;
        }
        i++;
    }

    return str_puntero;
}

bool string_is_symmetric(const char *str){
    size_t tam = string_length(str);
    size_t j = tam - 1;
    size_t i = 0;
    bool capicua = true;

    while (i < j){
        if (str[i] != str[j]){
            capicua = false;
        }
        j--;
        i++;
    }

    return capicua;
}