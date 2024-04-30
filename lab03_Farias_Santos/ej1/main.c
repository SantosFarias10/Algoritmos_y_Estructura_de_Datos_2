#include <stdlib.h>
#include <stdio.h>

#define MAX_SIZE 1000

static void dump(char a[], unsigned int length) {
    printf("\"");
    for (unsigned int j=0u; j < length; j++) {
        printf("%c", a[j]);
    }
    printf("\"");
    printf("\n");
}

unsigned int data_from_file(const char *path, unsigned int indexes[], char letters[], unsigned int max_size) {
    
    unsigned int length = 0u;
    FILE *file = NULL;
    file = fopen(path, "r");

    if (file == NULL) {
        printf("Error! Archivo No Existe.\n");
        exit(EXIT_FAILURE);
    }
    
    while (length < max_size && feof(file) == 0){
        
        int res = fscanf(file, "%u -> *%c*\n", &indexes[length], &letters[length]);
        
        if(res != 2){
            printf("Error! Formato del Archivo No Valido.\n");
            return 0u;
        }

        if (indexes[length] > max_size){
            printf("Error! Indice del Archivo Supera Max Size=%u.\n",max_size);
            return 0u;
        }
        
        if (ferror(file) != 0){
            printf("Error! de Lectura.\n");
            clearerr(file);
            exit(EXIT_FAILURE);
        }
        
        length++;
    }
 
    fclose(file);
    return length;
}

void sort_letters(unsigned int indexes[], char letters[], char sorted[], unsigned int length) {
    for (unsigned int i = 0; i < length; i++){
        sorted[indexes[i]] = letters[i];
    }
}

char *parce_filepath(int argc, char *argv[]) {
    char *result = NULL;

    if (argc < 2){
        exit(EXIT_FAILURE);
    }
    
    result = argv[1];
    
    return result;
}

int main(int argc, char *argv[]) {
    const char *filePath = parce_filepath(argc, argv);
    unsigned int indexes[MAX_SIZE];
    char letters[MAX_SIZE];
    char sorted[MAX_SIZE];

    unsigned int length = data_from_file(filePath, indexes, letters, MAX_SIZE); 
    
    if (length == 0u){
        return EXIT_FAILURE;
    }
    
    sort_letters(indexes, letters, sorted, length);

    dump(sorted, length);

    return EXIT_SUCCESS;
}