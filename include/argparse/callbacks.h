#ifndef CALLBACKS
#define CALLBACKS

#include <time.h>

void cb_help(Arguments *arguments, Token **t);

void cb_version(Arguments *arguments, Token **t);

void cb_quiet(Arguments *arguments, Token **t);

void cb_lambda(Arguments *arguments, Token **t);

void cb_operators(Arguments *arguments, Token **t);

void cb_number_of_days(Arguments *arguments, Token **t);

void cb_queue_size(Arguments *arguments, Token **t);

void cb_shift(Arguments *arguments, Token **t);

void cb_duration(Arguments *arguments, Token **t);

void cb_output_file(Arguments *arguments, Token **t);


#endif