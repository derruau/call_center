#ifndef ARGPARSE_MISC
#define ARGPARSE_MISC

#include <stdio.h>
#include <time.h>
#include <string.h>
#include <stdbool.h>
#include "argparse/types.h"

void misc_print_arguments(Arguments *a);

void misc_print_token(Token token);

void misc_print_token_list(Token *t, int size);

#endif