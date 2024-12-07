#ifndef SIM_MISC
#define SIM_MISC

#include <stdio.h>
#include <time.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>
#include "sim/types.h"
#include "sim/queue.h"

void misc_print_call(Call *c);

void misc_print_call_queue(Queue *q);

void misc_print_int_queue(Queue *q);

float misc_gen_poisson(float lambda, bool seed);

float misc_gen_uniform(float min, float max, bool seed);

time_t misc_add_seconds(time_t t1, int t2);

time_t misc_to_seconds(int time);

char* misc_get_random_name_from_file(char *path, char* name_ptr);

#endif