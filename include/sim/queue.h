#ifndef HEADER_QUEUE
#define HEADER_QUEUE

#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include "sim/types.h"

Queue *queue_init(int size_of_queue);

bool queue_is_empty(Queue *q);

bool queue_is_full(Queue *q);

void queue_enqueue(Queue *q, void *value);

void *queue_dequeue(Queue *q);

void *queue_peek(Queue *q);

#endif