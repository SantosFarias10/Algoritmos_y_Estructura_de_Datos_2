#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 100000

void print_help(char *program_name) {
    printf("Usage: %s <input file path>\n\n"
           "Loads an array given in a file in disk and prints it on the screen."
           "\n\n"
           "The input file must have the following format:\n"
           " * The first line must contain only a positive integer,"
           " which is the length of the array.\n"
           " * The second line must contain the members of the array"
           " separated by one or more spaces. Each member must be an integer."
           "\n\n"
           "In other words, the file format is:\n"
           "<amount of array elements>\n"
           "<array elem 1> <array elem 2> ... <array elem N>\n\n",
           program_name);
}

char *parse_filepath(int argc, char *argv[]) {
    char *result = NULL;
    bool valid_args_count = (argc == 2);

    if (!valid_args_count) {
        print_help(argv[0]);
        exit(EXIT_FAILURE);
    }

    result = argv[1];

    return result;
}

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


int main(int argc, char *argv[]) {
    char *filepath = NULL;

    filepath = parse_filepath(argc, argv);
    
    int array[MAX_SIZE];
    
    unsigned int length = array_from_file(array, MAX_SIZE, filepath);
    
    array_dump(array, length);
    
    return EXIT_SUCCESS;
}
