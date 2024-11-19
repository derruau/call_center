#ifndef HEADER_STACK
#define HEADER_STACK

#include <stdlib.h> 
#include <stdbool.h>

typedef struct stack {
    int size;
    int top;
    void *s[];
} Stack;

Stack *stack_init(int size_of_stack);

void stack_push(Stack *s, void *el);

void *stack_pop(Stack *s);

bool stack_is_empty(Stack *s);

bool stack_is_full(Stack *s);

void *stack_peek(Stack *s);

#endif