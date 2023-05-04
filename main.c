#include "stack.h"
#include <time.h>

void print_int(Data data);

int main(int argc, char** argv) {
    Stack stack = NULL;
    time_t t;

    srand((unsigned) time(&t));

    if ((stack = Stack_new(free, print_int)) != NULL) {
        printf("Ok!\n");

        int* x = NULL;
        for (size_t i = 0; i < 5; i++) {
            if ((x = (int*) malloc(sizeof(int))) != NULL) {
                *x = rand() % 100;

                Stack_push(stack, x);
            }
        }

        Stack_print(stack, NULL);

        print_int(Stack_peek(stack));
        printf("\n");
        Stack_print(stack, NULL);

        Stack_destroy(&stack);

        Stack_print(stack, NULL);
    }

    return EXIT_SUCCESS;
}

void print_int(Data data) {
    printf("%d", *((int*) data));

    return ;
}