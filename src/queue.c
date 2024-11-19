#include <stdlib.h> 

typedef struct stack {
    struct stack *next;
    void *value;
    
} Stack;


Stack *create_stack(void *value) {
    Stack *s =malloc(sizeof(Stack));

    s->next = NULL;
    s->value = value;

    return value;
}

Stack *stack_push(Stack *s, void *value) {
    Stack *ws = create_stack(value);

    ws->next = s;

    return ws;
}

Stack *stack_pop(Stack *s) {
    
}