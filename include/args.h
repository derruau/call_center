#ifndef ARGS
#define ARGS

#include <time.h>
#include "tokenizer.h"

typedef struct s_arguments {
    int help;
    int version;
    float lambda;
    float operators;

    // Corresponds to the -d argument
    time_t minsrv;
    time_t maxsrv;

    // Corresponds to the -s argument
    time_t shift_opening;
    time_t shift_closing;
} Arguments;

Arguments *args_create_arguments();

int args_handle(int argc, char *argv[], Arguments *arguments);

#endif