#ifndef ARGS
#define ARGS

#include <time.h>
#include "tokenizer.h"
#include "types.h"

Arguments *parser_create_arguments();

int parser_parse_args(int argc, char *argv[], Arguments *arguments);

#endif