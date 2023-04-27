#ifndef STACK_H
#define STACK_H

/* ================================================================ */

#include "data.h"
#include "guard/guard.h"

typedef struct _stack_node* Node;       /* A pointer to an incomplite type */

typedef struct _stack* Stack;           /* A pointer to an incomplite type */

/* ================================ */

extern Stack Stack_new(void (*fptr_desctroy)(void*), void (*fptr_print)(const Data));

extern void Stack_print(const Stack stack, void (*fptr_print)(const Data));

extern void Stack_destroy(Stack* stack);

extern int8_t Stack_push(Stack stack, const Data data);

extern Data Stack_pop(Stack stack);

extern Data Stack_peek(const Stack stack);

extern ssize_t Stack_get_size(const Stack stack);

/* ================================================================ */

#endif