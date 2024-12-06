/* 
========================================== MISC.C ==========================================
This file contains all of the miscellaneous functions that are debugging-related or are
too general to fit into any other file. 
========================================== MISC.C ==========================================
*/

#include <stdio.h>
#include <time.h>
#include <string.h>
#include <stdbool.h>
#include "argparse/types.h"

void misc_print_arguments(Arguments *a) {
    printf("Argument { \n");
    printf("   int help: %i\n", a->help);
    printf("   int version: %i\n", a->version);
    printf("   int quiet: %i\n", a->quiet);
    printf("   float lambda: %f\n", a->lambda);
    printf("   int operators: %i\n", a->operators);
    printf("   int number_of_days: %i\n\n", a->number_of_days);
    printf("   time_t minsrv: %li\n", a->minsrv);
    printf("   time_t maxsrv: %li\n\n", a->maxsrv);
    printf("   time_t shift_opening: %li\n", a->shift_opening);
    printf("   time_t shift_closing: %li\n\n", a->shift_closing);
    printf("   char* path: %s\n", a->path);
    printf("}\n");
}

void misc_print_token(Token token) {
    if (token.type == FLAG) {
        if (token.data.f == 0) return;
        printf("Token{type: FLAG, name: %s}\n", (char*)token.data.f->name);
    } else if (token.type == VALUE)
    {
        switch (token.data.v->type)
        {
        case INT:
            printf("Token{type: VALUE, {data: %i, type: INT}}\n", *(int*)token.data.v->data);
            break;
        case FLOAT:
            printf("Token{type: VALUE, {data: %f, type: FLOAT}}\n", *(float*)token.data.v->data);
            break;
        case DURATION:
            printf("Token{type: VALUE, {data: %s, type: DURATION}}\n", (char*)token.data.v->data);
            break;
        case DURATION_UNIT:
            printf("Token{type: VALUE, {data: %s, type: DURATION_UNIT}}\n", (char*)token.data.v->data);
            break;
        case STRING:
            printf("Token{type: VALUE, {data: %s, type: STRING}}\n", (char*)token.data.v->data);
            break;
        default:
            break;
        }
    }
}

void misc_print_token_list(Token *t, int number_of_tokens) {

    for (int i=0; i < number_of_tokens; i++) {
        
        misc_print_token(t[i]);

        if (i == number_of_tokens -1) {
            printf("\n");
            break;
        };
        printf("  -->  ");
    }
}