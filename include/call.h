#ifndef HEADER_CALL
#define HEADER_CALL

//#include "helper.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

typedef struct call {
    int id;
    char *tel;
    char *client_name;
    time_t call_start;
    time_t wait_time;
    time_t call_end;
} Call;

Call *call_create_random(int id, time_t call_start, time_t call_end);

void call_free(Call *c);

Call **call_create_n_random(
    int n,
    time_t shift_start, 
    time_t shift_end, 
    float lamba,
    float minsrv,
    float maxsrv
    
    );

#endif