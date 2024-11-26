#include "../include/queue.h"
#include "../include/stack.h"
#include "../include/call.h"
#include <stdio.h>
#include <math.h>
#include <time.h>
#include <string.h>

#define INVALID_PATH 301

#define POISSON_MAX 32768
#define MAX_NAME_LENGTH 32

void helper_print_call(Call *c) {
    printf("{ call_id:%i, tel:%s }", c->id, c->tel);
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

char* helper_get_random_name_from_file(char *path) {
    FILE *f = fopen(path, "r");

    if (f == NULL) exit(INVALID_PATH);

    fseek(f, 0L, SEEK_END);
    long size = ftell(f); // Gets the position of the file pointer
 
    // Sets the position to a random character of the file
    srand(time(NULL));
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
    char *full_name = malloc(sizeof(char)* (name_size + surname_size) );
    strcpy(full_name, name);
    strcat(full_name, " ");
    strcat(full_name, surname);

    return full_name;
    
}