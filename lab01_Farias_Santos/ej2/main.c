/* First, the standard lib includes, alphabetically ordered */
#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

/* Maximum allowed length of the array */
#define MAX_SIZE 100000

void print_help(char *program_name) {
    /* Print the usage help of this program. */
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
    /* Parse the filepath given by command line argument. */
    char *result = NULL;
    // Program takes exactly two arguments
    // (the program's name itself and the input-filepath)
    bool valid_args_count = (argc == 2);

    if (!valid_args_count) {
        print_help(argv[0]);
        exit(EXIT_FAILURE);
    }

    result = argv[1];

    return result;
}

unsigned int array_from_stdin(int array[], unsigned int max_size) {

    unsigned int size;

    printf("Ingrese el Tamaño del Arreglo: "); //le pedimos al usuario el tamaño del array
    scanf("%u", &size);

    if (size > max_size) { //verficamos que no se exceda del max_size
        printf("ERROR! El Tamaño es Superior al Permitido (100000).\n");
        return 0u;
    }

    printf("Ingrese los Valores del Arreglo.\n"); //pedimos que ingrese los valores del array
    for (unsigned int i = 0; i < size; i++) {
        printf("a[%d]=", i);
        scanf("%d", &array[i]);
    }
    
    printf("Datos Recolectados con Exito.\n");

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


int main(void) {
    int array[MAX_SIZE];

    unsigned int length = array_from_stdin(array, MAX_SIZE);
    
    array_dump(array, length);
    
    return EXIT_SUCCESS;
}
