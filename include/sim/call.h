#ifndef HEADER_CALL
#define HEADER_CALL

//#include "helper.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "sim/types.h"
#include "sim/misc.h"

Call *call_create_random(int id, time_t call_start, time_t call_duration, int day, int include_names, char *names_path);

void call_free(Call *c);

Call **call_create_n_random(
    int n,
    time_t shift_start, 
    time_t shift_end, 
    float lamba,
    float minsrv,
    float maxsrv,
    int day,
    int include_names,
    char *names_path
    );

#endif