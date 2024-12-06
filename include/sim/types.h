#ifndef SIM_TYPES
#define SIM_TYPES

#include <time.h>

typedef struct call {
    int id;
    char *tel;
    char *client_name;
    time_t call_start;
    time_t wait_time;
    time_t call_end;
} Call;

typedef struct {
    int front;
    int back;
    int size;
    int number_of_elements;
    void *q[];
} Queue;

#endif