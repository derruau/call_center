#ifndef ARGS
#define ARGS

#include <time.h>
#include "tokenizer.h"
#include "arg_types.h"

Arguments *args_create_arguments();

int args_handle(int argc, char *argv[], Arguments *arguments);

#endif