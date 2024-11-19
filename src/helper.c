#include "../include/queue.h"
#include "../include/stack.h"
#include "../include/call.h"
#include <stdio.h>

void helper_print_call_queue(Queue *q) {
    if (queue_is_empty(q)) return;

    int n = q->number_of_elements;
    for (int i=0; i < q->size; i++) {
        int idx = (q->front + i ) % q->size;
        Call *c = (Call*)q->q[idx];

        if (n == 0) break;
        n--;

        print_call(c);
    }
    printf("\n");
}

void helper_print_int_queue(Queue *q) {
    if (queue_is_empty(q)) return;

    int n = q->number_of_elements;
    for (int i=0; i < q->size; i++) {
        int idx = (q->front + i ) % q->size;
        int *c = (int*)q->q[idx];

        if (n == 0) break;
        n--;

        printf("%i ", *c);
    }
    printf("\n");
}

void helper_print_call(Call *c) {
    printf("{ call_id:%i, tel:%s }", c->id, c->tel);
}