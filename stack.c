#include "stack.h"

struct _stack_node {
    Data data;

    struct _stack_node* next;
};

struct _stack {
    size_t size;

    struct _stack_node* top;
    struct _stack_node* bottom;

    void (*fptr_destroy)(void*);        /* Destroys every element of the stack */
    void (*fptr_print)(const Data);     /* Displays a stack */
};

/* ================================================================ */

static Node Node_new(Data data) {
    Node node = NULL;

    if (data != NULL) {
        if ((node = (Node) malloc(sizeof(struct _stack_node))) != NULL) {
            node->data = data;
            node->next = NULL;
        }
        else {
            warn_with_sys_msg(__func__);
        }
    }
    else {
        warn_with_user_msg(__func__, "data can't be NULL");
    }

    return node;
}

static Data Node_destroy(Node* node) {
    Data data = NULL;

    if ((node != NULL) && (*node != NULL)) {
        data = (*node)->data;
        (*node)->next = NULL;

        /* Clear memory*/
        memset(*node, 0, sizeof(struct _stack_node));
        /* Deallocate memory */
        free(*node);

        *node = NULL;
    }

    return data;
}

/* ================================ */

Stack Stack_new(void (*fptr_desctroy)(void*), void (*fptr_print)(const Data)) {
    Stack stack = NULL;

    if ((stack = (Stack) malloc(sizeof(struct _stack))) != NULL) {
        stack->size = 0;
        stack->top = stack->bottom = NULL;

        stack->fptr_destroy = fptr_desctroy;
        stack->fptr_print = fptr_print;
    }
    else {
        warn_with_sys_msg(__func__);
    }

    return stack;
}

/* ================================ */

void Stack_print(const Stack stack, void (*fptr_print)(const Data)) {
    void (*alt_fptr_print)(const Data) = NULL;

    if (stack != NULL) {
        if ((stack->fptr_print == NULL) && (fptr_print == NULL)) {
            warn_with_user_msg(__func__, "there is no associated `print` function with the list");

            return ;
        }

        printf("[");

        if (stack->size > 0) {
            alt_fptr_print = (stack->fptr_print == NULL) ? fptr_print : stack->fptr_print;

            for (Node node = stack->bottom; node != NULL; node = node->next) {
                alt_fptr_print(node->data);

                if (node->next != NULL) {
                    printf(" <- ");
                }
            }
        }

        printf("]\n");
    }
    else {
        warn_with_user_msg(__func__, "provided stack is NULL");
    }

    return ;
}

/* ================================ */

void Stack_destroy(Stack* stack) {
    Data data = NULL;

    if ((stack != NULL) && (*stack != NULL)) {
        while ((*stack)->size > 0) {
            data = Stack_pop(*stack);

            if ((*stack)->fptr_destroy != NULL) {
                (*stack)->fptr_destroy(data);
            }
        }

        /* Clear memory */
        memset(*stack, 0, sizeof(struct _stack));
        /* Dealloce memory */
        free(*stack);

        *stack = NULL;
    }
    else {
        warn_with_user_msg(__func__, "provided stack pointer and/or stack is NULL");
    }

    return ;
}

/* ================================ */

Data Stack_pop(Stack stack) {
    Node node = NULL;
    Data data = NULL;


    if (stack != NULL) {
        if (stack->size > 0) {
            node = stack->top;
            data = Node_destroy(&node);

            if (stack->size == 1) {
                stack->top = stack->bottom = NULL;
            }
            else {
                Node temp = NULL;

                for (temp = stack->bottom; temp->next != stack->top; temp = temp->next) ;

                stack->top = temp;
                temp->next = NULL;
            }

            stack->size--;
        }
    }
    else {
        warn_with_user_msg(__func__, "provided stack is NULL");
    }

    return data;
}

/* ================================ */

int8_t Stack_push(Stack stack, const Data data) {
    int8_t result = 0;
    Node node = NULL;

    if (stack != NULL) {
        if ((node = Node_new(data)) != NULL) {
            switch (stack->size) {
                case 0:
                    stack->top = stack->bottom = node;

                    break ;

                default:
                    stack->top->next = node;
                    stack->top = node;

                    break ;
            }

            stack->size++;
            result = 1;
        }
    }
    else {
        warn_with_user_msg(__func__, "provided stack is NULL");
    }

    return result;
}

/* ================================ */

ssize_t Stack_get_size(const Stack stack) {
    return (stack != NULL) ? stack->size : -1;
}

/* ================================ */

Data Stack_peek(const Stack stack) {
    Data data = NULL;

    if (stack != NULL) {
        if (stack->size > 0) {
            data = stack->top->data;
        }
    }
    else {
        warn_with_user_msg(__func__, "provided stack is NULL");
    }

    return data;
}