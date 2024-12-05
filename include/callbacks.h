#ifndef CALLBACKS
#define CALLBACKS

#include <time.h>

time_t str_to_time(char* s);

void cb_help(Arguments *arguments, Token **t);

void cb_version(Arguments *arguments, Token **t);

void cb_lambda(Arguments *arguments, Token **t);

void cb_shift(Arguments *arguments, Token **t);

void cb_duration(Arguments *arguments, Token **t);

void cb_number_of_days(Arguments *arguments, Token **t);

void cb_operators(Arguments *arguments, Token **t);


#endif