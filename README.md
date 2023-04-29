# Stack

## Content

[About](#about)

[API](#api)

[Examples](#examples)

[Resources](#resources)

## About

Stack is  an efficient data structures for storing and retrieving data in a last-in, first-out, or LIFO, order. This allows us to retrieve data in the opposite order as it was stored.

The `Stack` is a pointer to an incomplete type,

```C
typedef struct _stack* Stack;
```

which means users are only allowed to work with stacks through the use of specified functions (e.g., interfaces, the **first-class ADT pattern**).

## API

### Stack_new

```C
Stack Stack_new(void (*fptr_desctroy)(void*), void (*fptr_print)(const Data))
```

The `Stack_new` function allocates a new instance of a stack data type.

| Type | Description |
| ---- | ----------- |
| `void (*fptr_destroy)(void*)` | Provides a way to free dynamically allocated data when `Stack_destroy` is called. If the stack contains data dynamically allocated using `malloc`, `destroy` should be set to `free` to free the data as the stack is destroyed. For structured data containing several dynamically allocated members, destroy should be set to a user-defined function that calls `free` for each dynamically allocated member as well as for the structure itself. For a stack containing data that should not be freed, destroy should be set to *NULL* |
| `void (*fptr_print)(const Data)` | Provides a default way to display content of the stack when `Stack_display` is invoked. [How to write `print` functions](#how-to-write-print-functions) |

**Return value**: `Stack` if creating a new stack is successful, or `NULL` otherwise.

### Stack_print

```C
void Stack_print(const Stack stack, void (*fptr_print)(const Data));
```

The `Stack_print` function outputs content of the stack. The `fptr_print` argument is a callback function that is called on every node while traversng the stack. If `fptr_print` is NULL, the `fptr_print` function specified in `Stack_new` is used.

| Type | Description |
| ---- | ----------- |
| `const Stack stack` | The stack to be displayed |
| `void (*fptr_print)(const Data)` | The callback function to handle data in a node |

**Return value**: None

### Stack_destroy

```C
void Stack_destroy(Stack* stack);
```

The `Stack_destroy` function destroys a stack. Primarally this means removing all elements from the stack. The function passed to `Stack_new` is called once for each element as it is removed, provided `fptr_destroy` was not set to *NULL*. Upon return, the stack (e.g., `stack`) is `NULL`.

| Type | Description |
| ---- | ----------- |
| `Stack* stack` | A pointer to a stack to be destroyed |

**Return value**: None

### Stack_push

```C
int8_t Stack_push(Stack stack, const Data data);
```

The `Stack_push` function pushes an element onto the stack specified by `stack`. The new element contains a pointer to `data`, so the memory referenced by `data` should remain valid as long as the element remains in the stack. It is the responsibility of the caller to manage the storage associated with data.

| Type | Description |
| ---- | ----------- |
| `Stack stack` | The stack to push an element onto |
| `const Data data` | Data to be pushed |

**Return value**: 1 if pushing the element is successful, or 0 otherwise.

### Stack_pop

```C
Data Stack_pop(Stack stack);
```

The `Stack_pop` function pops an element off the stack specified by `stack`. It is the responsibility of the caller to manage the storage associated with the returned data.

| Type | Description |
| ---- | ----------- |
| `Stack stack` | The stack to pop an element off |

**Return value**: `Data` if popping the element is successful, or `NULL` otherwise.

### Stack_peek

```C
Data Stack_peek(const Stack stack);
```

The `Stack_peek` function return `Data` stored in the element at the top of the stack specified by `stack`.

| Type | Description |
| ---- | ----------- |
| `const Stack stack` | A stack to peek |

**Return value**: `Data` if a stack is not empty, or `NULL` otherwise.

### Stack_get_size

```C
ssize_t Stack_get_size(const Stack stack);
```

| Type | Description |
| ---- | ----------- |
| `const Stack stack` | A stack which size to get |

**Return value**: number of elements in the stack, or -1 if stack is `NULL`.

## Examples

### How to write `print` functions

The `fptr_print` argument in the `Stack_print` and `Stack_new` functions is a callback that handles data in a stack node.

One must assume that a stack is homogeneous (e.g., contains data of the same type). For example, suppose we have a stack of integers, then we might write the function:

```C
/* ... */
void print_int(Data data) {
    printf("%d", *((int*) data));
}
```

Keep in mind that `fptr_print` expects its argument to be a type of `Data`.

## Resources

[Mastering Algorithms with C](https://www.amazon.com/Mastering-Algorithms-Techniques-Sorting-Encryption/dp/1565924533/ref=sr_1_1?crid=1ZN4ENEQEGO5&keywords=mastering+c+algorithms&qid=1679619546&s=books&sprefix=mastering+c+algoritms%2Cstripbooks-intl-ship%2C221&sr=1-1) by Kyle Loudon.

[Data Structures, Algorithms, and Software Principles in C](https://www.amazon.com/Data-Structures-Algorithms-Software-Principles/dp/0201591189/ref=sr_1_10?crid=14MCGWUKW0F98&keywords=data+structures+and+algorithms+in+C&qid=1679784448&s=books&sprefix=data+structures+and+algorithms+in+c%2Cstripbooks-intl-ship%2C186&sr=1-10) by Thomas Standish.

[Computer Systems: A Programmer's Perspective](https://www.amazon.com/Computer-Systems-Programmers-Randal-Bryant/dp/013034074X/ref=sr_1_3?crid=1NDI8BHE4BPQM&keywords=computer+systems+a+programmer%27s+perspective&qid=1679784732&s=books&sprefix=computer+pers%2Cstripbooks-intl-ship%2C199&sr=1-3) by Randal E. Bryant, David Richard O'Hallaron.

[Patterns in C](https://leanpub.com/patternsinc) by Adam Tornhill
