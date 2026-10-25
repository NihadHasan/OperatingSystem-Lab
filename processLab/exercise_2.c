#include <stdio.h>
#include <stdlib.h>

int global_var = 10;

int main() {
    int stack_var = 20;
    int *heap_var = malloc(sizeof(int));

    *heap_var = 30;

    printf("Global: %p\n", (void*)&global_var);
    printf("Stack:  %p\n", (void*)&stack_var);
    printf("Heap:   %p\n", (void*)heap_var);

    free(heap_var);
    return 0;
}