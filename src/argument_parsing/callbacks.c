#include <time.h>
#include <string.h>
#include <stdlib.h>
#include "../../include/arg_types.h"

time_t str_to_time(char* s) {
    size_t l = strlen(s);

    struct tm *t = malloc(sizeof(struct tm));

    switch (s[l - 1])
    {
    case 's':
        s[l - 1] = '\0';
        t->tm_sec = strtol(s, NULL, 10);
        return mktime(t);
    case 'm':
        s[l - 1] = '\0';
        t->tm_min = strtol(s, NULL, 10);
        return mktime(t);
    case 'h':
        s[l - 1] = '\0';
        t->tm_hour = strtol(s, NULL, 10);
        return mktime(t);
    case 'd':
        s[l - 1] = '\0';
        t->tm_mday = strtol(s, NULL, 10);
        return mktime(t);
    case 'w':
        s[l - 1] = '\0';
        t->tm_mday= strtol(s, NULL, 10)*7;
        return mktime(t);
    case 'M':
        s[l - 1] = '\0';
        t->tm_mon = strtol(s, NULL, 10);
        return mktime(t);
    case 'y':
        s[l - 1] = '\0';
        t->tm_year = strtol(s, NULL, 10);
        return mktime(t);
    
    default:
        return -1;
    }
}

void cb_help(Arguments *arguments, Token **t) {
    arguments->help = 1;
}

void cb_version(Arguments *arguments, Token **t) {
    arguments->version = 1;
}

void cb_lambda(Arguments *arguments, Token **t) {
    // There is only one argument with this callback 
    arguments->lambda = *(float*)t[0]->data.v->data;
}

void cb_shift(Arguments *arguments, Token **t) {
    char *_otmp = (char*)t[0]->data.v->data;
    arguments->shift_opening = str_to_time(_otmp);


    char *_ctmp = (char*)t[1]->data.v->data;
    arguments->shift_closing = str_to_time(_ctmp);
}

void cb_duration(Arguments *arguments, Token **t) {
    char *minsrv = (char*)t[0]->data.v->data;
    arguments->minsrv = str_to_time(minsrv);


    char *maxsrv = (char*)t[1]->data.v->data;
    arguments->maxsrv = str_to_time(maxsrv);
}

void cb_number_of_days(Arguments *arguments, Token **t) {
    // There is only one argument with this callback 
    arguments->number_of_days = *(int*)t[0]->data.v->data;
}

void cb_operators(Arguments *arguments, Token **t) {
    // There is only one argument with this callback 
    arguments->operators = *(int*)t[0]->data.v->data;
}