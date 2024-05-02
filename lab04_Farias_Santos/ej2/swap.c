#include <stdlib.h>
#include <stdio.h>

void swap(int *a, int *b){
    int aux;
    aux = *a;
    *a = *b;
    *b = aux;
}

int main(){
    int x = 0, y = 0, r = 0;
    
    x = 6;
    y = 4;
    
    printf("X = %d, Y = %d\n", x, y);
    
    swap(&x, &y);

    printf("X = %d, Y = %d\n",x, y);

    return r;
}