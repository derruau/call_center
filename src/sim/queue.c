/* 
========================================== QUEUE.C ==========================================
This file's role is to contain all the functions related to the Queue struct defined in
sim/types.c

You will find every useful function a queue has, such as:
    - Queue Initialisation
    - Is empty
    - Is full
    - Enqueue
    - Dequeue
    - Peek

You shouldn't need to take a look inside the Queue struct and only manipulate it using the
provided functions.
========================================== QUEUE.C ==========================================
*/

#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include "sim/types.h"

#define QUEUE_IS_FULL 100
#define QUEUE_IS_EMPTY 101

// Initializes an empty queue of size 'size_of_queue'
Queue *queue_init(int size_of_queue) {
    Queue *q = malloc(sizeof(Queue) + sizeof(void*)*size_of_queue);

    q->size = size_of_queue;
    q->number_of_elements = 0;
    q->back = 0;
    q->front = 0;

    return q;
}

// Checks if a queue is empty
bool queue_is_empty(Queue *q) {
    return (q->number_of_elements == 0);
}

// Checks if a queue is full
bool queue_is_full(Queue *q) {
    return (q->number_of_elements == q->size);
}

// Enqueues a value in a queue
void queue_enqueue(Queue *q, void *value) {
    if (queue_is_full(q)) exit(QUEUE_IS_FULL);

    q->number_of_elements++;
    q->q[q->back] = value;
    q->back = (q->back + 1) % q->size;
}

// Dequeues a value from a queue
void *queue_dequeue(Queue *q) {
    if (queue_is_empty(q)) exit(QUEUE_IS_EMPTY);

    void *v = q->q[q->front];

    q->number_of_elements--;
    q->front = (q->front + 1) % q->size;

    return v;
}

// Returns the value that is about to be dequeued without
// actually dequeuing it.
void *queue_peek(Queue *q) {
    if (queue_is_empty(q)) exit(QUEUE_IS_EMPTY);

    return q->q[q->front];
}