#ifndef HEADER_HELPER
#define HEADER_HELPER

#include "queue.h"
#include "stack.h"
#include "call.h"
#include "argparse/types.h"
#include <stdio.h>

void helper_print_call(Call *c);

void helper_print_call_queue(Queue *q);

void helper_print_int_queue(Queue *q);

float helper_gen_poisson(float lambda, bool seed);

float helper_gen_uniform(float min, float max, bool seed);

time_t helper_add_seconds(time_t t1, int t2);

char* helper_get_random_name_from_file(char *path, char* name_ptr);

void helper_print_arguments(Arguments *a);

void helper_print_token(Token token);

void helper_print_tokens(Token *t, int size);

#endif