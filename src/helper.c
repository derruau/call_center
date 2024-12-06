#include <stdio.h>
#include <time.h>
#include <string.h>
#include <stdbool.h>
#include "sim/types.h"
#include "argparse/types.h"

#define INVALID_PATH 301

#define POISSON_MAX 32768
#define MAX_NAME_LENGTH 32

void helper_print_call(Call *c) {
    printf("Call{ call_id:%i, name: %s, tel:%s }\n", c->id, c->client_name,  c->tel);
}

void helper_print_call_queue(Queue *q) {
    if (queue_is_empty(q)) return;

    int n = q->number_of_elements;
    for (int i=0; i < q->size; i++) {
        int idx = (q->front + i ) % q->size;
        Call *c = (Call*)q->q[idx];

        if (n == 0) break;
        n--;

        helper_print_call(c);
    }
    printf("\n");
}

void helper_print_int_queue(Queue *q) {
    if (queue_is_empty(q)) return;

    int n = q->number_of_elements;
    for (int i=0; i < q->size; i++) {
        int idx = (q->front + i ) % q->size;
        int *c = (int*)q->q[idx];

        if (n == 0) break;
        n--;

        printf("%i ", *c);
    }
    printf("\n");
}


float helper_gen_poisson(float lambda, bool seed) {
    if (seed) srand(time(NULL));

    float u = (rand() % POISSON_MAX) / POISSON_MAX;

    return -log(1 - u) / lambda;
} 

float helper_gen_uniform(float min, float max, bool seed) {
    if (seed) srand(time(NULL));

    int i = (int)(max - min);

    return (rand() % i) / i;
}

time_t helper_add_seconds(time_t t1, int t2) {
    // Adds t1 to t2.
    // Important: t2 is in seconds!!
    struct tm *t = gmtime(&t1);

    t->tm_sec += t2;

    time_t result = mktime(t);

    return result;
}

char* helper_get_random_name_from_file(char *path, char* name_ptr) {
    FILE *f = fopen(path, "r");

    if (f == NULL) exit(INVALID_PATH);

    fseek(f, 0L, SEEK_END);
    long size = ftell(f); // Gets the position of the file pointer
 
    // Sets the position to a random character of the file
    long start_pos = (long)(rand() % (size - 1));
    fseek(f, start_pos, SEEK_SET);

    int c = fgetc(f);
    while ((c != EOF)) {
        c = fgetc(f);
        if (c == '\n') break;
    }

    char name[MAX_NAME_LENGTH];
    char surname[MAX_NAME_LENGTH];
    fscanf(f, "%[^,],%[^\n]", name, surname); // Parses a line of the file

    fclose(f);

    // String concatenation
    size_t name_size = strlen(name);
    size_t surname_size = strlen(surname);
    char *full_name = malloc(sizeof(char)* (name_size + surname_size + 1) );
    strcpy(full_name, name);
    strcat(full_name, " ");
    strcat(full_name, surname);


    name_ptr = malloc(sizeof(char)* (name_size + surname_size) );
    strcpy(name_ptr, full_name);

    return full_name;
    
}

void helper_print_arguments(Arguments *a) {
    printf("Argument { \n");
    printf("   int help: %i\n", a->help);
    printf("   int version: %i\n", a->version);
    printf("   int quiet: %i\n", a->quiet);
    printf("   float lambda: %f\n", a->lambda);
    printf("   int operators: %i\n", a->operators);
    printf("   int number_of_days: %i\n", a->number_of_days);
    printf("   time_t minsrv: %li\n", a->minsrv);
    printf("   time_t maxsrv: %li\n", a->maxsrv);
    printf("   time_t shift_opening: %li\n", a->shift_opening);
    printf("   time_t shift_closing: %li\n", a->shift_closing);
    printf("   char* path: %s\n", a->path);
    printf("}\n");
}

void helper_print_token(Token token) {
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

void helper_print_tokens(Token *t, int size) {

    for (int i=0; i < size; i++) {
        
        helper_print_token(t[i]);

        if (i == size -1) {
            printf("\n");
            break;
        };
        printf("  -->  ");
    }
}