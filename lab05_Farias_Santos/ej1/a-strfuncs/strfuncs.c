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