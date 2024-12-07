/* 
========================================== CALLBACKS.C ==========================================
This file contains all the callbacks for the different Rules defined in args.c

A callback (in this case) is a function that takes in some relevant Tokens and does some work on 
them if necessary. It then and puts the Token's data in an Argument struct at their designated 
place.

Please see the arg_types.c and args.c's documentation header for further information about these 
callbacks and how they integrate with the program.
========================================== CALLBACKS.C ==========================================
*/

//#define _GNU_SOURCE // We need this to call t->tm_gmtoff

#include <time.h>
#include <string.h>
#include <stdlib.h>
#include "argparse/types.h"

// Duration prefix definition
#define SECONDS 's'
#define MINUTES 'm'
#define HOUR 'h'
#define DAY 'd'
#define WEEK 'w'
#define MONTH 'M'
#define YEAR 'y'

// TODO: find a better way to remove tm_gmtoff that is Windows-compatible!!
// Should not be used outside of this file.
// Converts DURATION_UNIT Token data to time_tZ
time_t _cb_duration_unit_to_time(char* s) {
    size_t l = strlen(s);

    // Initalization of t to the epoch
    // The hard thing here is that time_t's unit is platform dependent
    // It is NOT guaranteed to be in seconds!
    time_t epoch = 0;
    struct tm *t = gmtime(&epoch);
    time_t normalization_factor = mktime(t);
    t->tm_isdst = 0;
    #ifdef _GNU_SOURCE
        t->tm_gmtoff = 0;
        t->tm_zone = "GMT";
    #endif

    switch (s[l - 1])
    {
    case SECONDS:
        s[l - 1] = '\0';
        t->tm_sec += strtol(s, NULL, 10);
        break;
    case MINUTES:
        s[l - 1] = '\0';
        t->tm_min += strtol(s, NULL, 10);
        break;
    case HOUR:
        s[l - 1] = '\0';
        t->tm_hour += strtol(s, NULL, 10);
        break;
    case DAY:
        s[l - 1] = '\0';
        t->tm_mday += strtol(s, NULL, 10);
        break;
    case WEEK:
        s[l - 1] = '\0';
        t->tm_mday += strtol(s, NULL, 10)*7;
        break;
    case MONTH:
        s[l - 1] = '\0';
        t->tm_mon += strtol(s, NULL, 10);
        break;
    case YEAR:
        s[l - 1] = '\0';
        t->tm_year += strtol(s, NULL, 10);
        break;
    default:
        return -1;
    }

    time_t result = mktime(t) - normalization_factor;
    return result;
}

void cb_help(Arguments *arguments, Token **t) {
    arguments->help = 1;
}

void cb_version(Arguments *arguments, Token **t) {
    arguments->version = 1;
}

void cb_quiet(Arguments *arguments, Token **t) {
    arguments->quiet = 1;
}

void cb_lambda(Arguments *arguments, Token **t) {
    if (t[0]->data.v->type == INT) arguments->lambda = *(int*) t[0]->data.v->data;
    else arguments->lambda = *(float*)t[0]->data.v->data;
}

void cb_shift(Arguments *arguments, Token **t) {
    char *_otmp = (char*)t[0]->data.v->data;
    arguments->shift_opening = _cb_duration_unit_to_time(_otmp);


    char *_ctmp = (char*)t[1]->data.v->data;
    arguments->shift_closing = _cb_duration_unit_to_time(_ctmp);
}

void cb_duration(Arguments *arguments, Token **t) {
    char *minsrv = (char*)t[0]->data.v->data;
    arguments->minsrv = _cb_duration_unit_to_time(minsrv);


    char *maxsrv = (char*)t[1]->data.v->data;
    arguments->maxsrv = _cb_duration_unit_to_time(maxsrv);
}

void cb_number_of_days(Arguments *arguments, Token **t) {
    arguments->number_of_days = *(int*)t[0]->data.v->data;
}

void cb_operators(Arguments *arguments, Token **t) {
    arguments->operators = *(int*)t[0]->data.v->data;
}