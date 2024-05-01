#include <stdlib.h>
#include <stdio.h>

#define MAX_SIZE 1000

unsigned int data_from_file(const char *path, unsigned int indexes[], char letters[], unsigned int max_size){ /*data_from_file lo que hace leer y rellenar los arreglos indexes[] y letters[] con los datos leidos los datos leidos del archivo indicado por path, ademas devuelva cuántos elementos efectivamente contenía dicho archivo*/
    unsigned int length = 0u;

    FILE *file = NULL;
    file = fopen(path, "r");

    if (file == NULL){
        printf("¡¡¡ERROR!!! El archivo no existe\n");
        exit(EXIT_SUCCESS);
    }

    while (length < max_size && feof(file) == 0){ /*el feof es igual a cero cuando no es la ultima linea leida, cuando llega al final del archivo devuelve un numero disinto de cero, entonces sale del while*/
        int res = fscanf(file, "%u -> *%c*\n", &indexes[length], &letters[length]); /*fscanf va a leer el archivo con el formato "%u -> *%c*" y a los valores %u lo va a almacenar en indexes[length] y los %c en letters[length]*/

        if (res != 2){
            printf("¡¡¡ERROR!!! Formato del archivo no valido\n");
            return 0u;
        }

        if (indexes[length] > max_size){
            printf("¡¡¡ERROR!!! Indice del archivo supera al max size\n");
            return 0u;
        }
        
        if (ferror(file) != 0){
            printf("¡¡¡ERROR DE LECTURA!!!\n");
            clearerr(file);
            exit(EXIT_FAILURE);
        }
        
        length++;
    }

    fclose(file);
    return length;
}

void sort_letters(unsigned int indexes[], char letters[], char sorted[], unsigned int length) { /*en char sorted[] vamos a ir guardando los valores ya ordenados*/
    for (unsigned int i = 0; i < length; i++){
        sorted[indexes[i]] = letters[i];
    }
}

static void dump(char a[], unsigned int length) {
    printf("\"");
    for (unsigned int j=0u; j < length; j++) {
        printf("%c", a[j]);
    }
    printf("\"");
    printf("\n\n");
}

char *parce_filepath(int argc, char *argv[]) { /*la funcion *parce_filepath se va a encargar de leer correctamente los argumentos*/
    char *result = NULL;

    if (argc < 2){
        exit(EXIT_FAILURE);
    }
    
    result = argv[1];
    
    return result;
}

int main(int argc, char *argv[]) { /*int argc es la cantidad de argumentos que toma main y *argv[] son los valores de los argumentos*/
    const char *filePath = parce_filepath(argc, argv);
    unsigned int indexes[MAX_SIZE];
    char letters[MAX_SIZE];
    char sorted[MAX_SIZE];
    unsigned int length = data_from_file(filePath, indexes, letters, MAX_SIZE); 

    if (length == 0u){
        exit(EXIT_SUCCESS);
    }
    
    sort_letters(indexes, letters, sorted, length);

    dump(sorted, length);

    return EXIT_SUCCESS;
}

