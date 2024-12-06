/* 
========================================== QUEUE.C ==========================================
This file's role is to contain all the structs defined in the sim folder.

Doing this prevents a lot of problems related to circular imports.
========================================== QUEUE.C ==========================================
*/

#include <time.h>

//================ call.c types ================
typedef struct call {
    int id;
    char *tel;
    char *client_name;
    time_t call_start;
    time_t wait_time;
    time_t call_end;
} Call;

//================ queue.c types ================

typedef struct {
    int front;
    int back;
    int size;
    int number_of_elements;
    void *q[];
} Queue;