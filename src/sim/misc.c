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
#include <math.h>
#include "sim/types.h"
#include "sim/queue.h"


#define INVALID_PATH 301
#define UNEXPECTED_ERROR 302
#define UNEXPECTED_ERROR_MESSAGE "[ERROR] - An unexpected error was encountered!"

#define POISSON_MAX 32768
#define MAX_NAME_LENGTH 32

void misc_print_call(Call *c) {
    printf("Call{ call_id:%i, name: %s, tel:%s }\n", c->id, c->client_name,  c->tel);
}

void misc_print_call_queue(Queue *q) {
    if (queue_is_empty(q)) return;

    int n = q->number_of_elements;
    for (int i=0; i < q->size; i++) {
        int idx = (q->front + i ) % q->size;
        Call *c = (Call*)q->q[idx];

        if (n == 0) break;
        n--;

        misc_print_call(c);
    }
    printf("\n");
}

void misc_print_int_queue(Queue *q) {
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


// TODO: remove the seed parameter and add an init_sim function
// that calls srand()
float misc_gen_exponential(float lambda, bool seed) {
    if (seed) srand(time(NULL));

    float u = (rand() % POISSON_MAX) / (float)POISSON_MAX;

    float ret = -log(1 - u) / lambda;

    return -log(1 - u) / lambda;
} 

float misc_gen_uniform(float min, float max, bool seed) {
    if (seed) srand(time(NULL));

    int i = (int)(max - min);

    if (i == 0) return min;

    float ret = (rand() % i) / (float)i;

    return min + (max - min)*ret;
}

// Adds t1 to t2.
// Important: t2 is in seconds!!
time_t misc_add_seconds(time_t t1, int t2) {
    struct tm *t = gmtime(&t1);

    t->tm_sec += t2;

    time_t result = mktime(t);

    return result;
}

time_t misc_int_to_seconds(int time) {
    time_t epoch = 0;
    struct tm *t = localtime(&epoch);
    
    t->tm_sec += time;
    
    time_t converted_time = mktime(t);

    return converted_time;
}

char* misc_get_random_name_from_file(char *path, char* name_ptr) {
    FILE *f = fopen(path, "r");

    if (f == NULL) exit(INVALID_PATH);

    if (fseek(f, 0L, SEEK_END) != 0) {
        printf(UNEXPECTED_ERROR_MESSAGE);
        exit(UNEXPECTED_ERROR);
    }
    long size = ftell(f); // Gets the position of the file pointer
 
    // Sets the position to a random character of the file
    long start_pos = (long)(rand() % (size - 1));
    fseek(f, start_pos, SEEK_SET);

    int c = fgetc(f);
    while ((c != EOF)) {
        c = fgetc(f);
        if (c == '\n') break;
    }

    char* name = malloc(sizeof(char)*MAX_NAME_LENGTH);
    char* surname = malloc(sizeof(char)*MAX_NAME_LENGTH);
    fscanf(f, "%[^,],%[^\n]", name, surname); // Parses a line of the file

    fclose(f);

    // String concatenation
    size_t name_size = strlen(name);
    size_t surname_size = strlen(surname);
    char *full_name = malloc(sizeof(char)* (name_size + surname_size + 2) );
    strcpy(full_name, name);
    strcat(full_name, " ");
    strcat(full_name, surname);

    return full_name;
    
}