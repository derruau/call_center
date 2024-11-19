#include <stdlib.h> 
#include <stdbool.h>

#define STACK_OVERFLOW 200
#define STACK_UNDERFLOW 201
#define STACK_IS_EMPTY 202

typedef struct stack {
    int size;
    int top;
    void *s[];
} Stack;

Stack *stack_init(int size_of_stack) {
    Stack *s = malloc(sizeof(Stack) + sizeof(void*)*size_of_stack);

    s->size = size_of_stack;
    s->top = -1;

    return s;
}

void stack_push(Stack *s, void *el) {
    if (s->top >= s->size) exit(STACK_OVERFLOW);
    
    s->top++;
    s->s[s->top] = el;
}

void *stack_pop(Stack *s) {
    if (s->top == -1) exit(STACK_UNDERFLOW);

    s->top--;
    return s->s[s->top - 1];
}

bool stack_is_empty(Stack *s) {
    return s->top == -1;
}

bool stack_is_full(Stack *s) {
    return s->top == (s->size -1);
}

void *stack_peek(Stack *s) {
    if (stack_is_empty(s)) exit(STACK_IS_EMPTY);
    return s->s[s->top];
}