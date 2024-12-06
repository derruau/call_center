#include "call.h"
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

#define QUEUE_IS_FULL 100
#define QUEUE_IS_EMPTY 101

typedef struct {
    int front;
    int back;
    int size;
    int number_of_elements;
    void *q[];
} Queue;

Queue *queue_init(int size_of_queue) {
    Queue *q = malloc(sizeof(Queue) + sizeof(void*)*size_of_queue);

    q->size = size_of_queue;
    q->number_of_elements = 0;
    q->back = 0;
    q->front = 0;

    return q;
}

bool queue_is_empty(Queue *q) {
    return (q->number_of_elements == 0);
}

bool queue_is_full(Queue *q) {
    return (q->number_of_elements == q->size);
}

void queue_enqueue(Queue *q, void *value) {
    if (queue_is_full(q)) exit(QUEUE_IS_FULL);

    q->number_of_elements++;
    q->q[q->back] = value;
    q->back = (q->back + 1) % q->size;
}

void *queue_dequeue(Queue *q) {
    if (queue_is_empty(q)) exit(QUEUE_IS_EMPTY);

    void *v = q->q[q->front];

    q->number_of_elements--;
    q->front = (q->front + 1) % q->size;

    return v;
}

void *queue_peek(Queue *q) {
    if (queue_is_empty(q)) exit(QUEUE_IS_EMPTY);

    return q->q[q->front];
}