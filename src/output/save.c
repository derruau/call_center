/* 
========================================== SAVE.C ==========================================
This file's role is to save the result of the simulation to a file

The results will be saved like so:

CALL_ID     TEL     CLIENT_NAME     CALL_START      CALL_END    CALL_WAIT_TIME


WARNING: This code is really ugly but I don't have the time to do better
========================================== SAVE.C ==========================================
*/
#include "argparse/types.h"
#include "sim/types.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#define SEPARATOR_CONSTANT 2

#define COULD_NOT_OPEN_SAVE_FILE 601
#define COULD_NOT_OPEN_SAVE_FILE_MESSAGE "[SAVE ERROR] - Could not open the output file!"

char *int_to_spaces(int n) {
    char *string_separator = malloc(sizeof(char)*(n + 1));
    for (int i = 0; i < n; i++) {
        string_separator[i] = ' ';
    }
    string_separator[n] = '\0';

    return string_separator;
}

void save_call(FILE *f, Call *c, int max_length[]) {
    int id_length = ceil(log10(c->id));
    char *id_spaces = int_to_spaces(max_length[0] - id_length + SEPARATOR_CONSTANT);

    int tel_length = strlen(c->tel);
    char *tel_spaces = int_to_spaces(max_length[1] - tel_length + SEPARATOR_CONSTANT);

    int name_length = strlen(c->client_name);
    char *name_spaces = int_to_spaces(max_length[2] - name_length + SEPARATOR_CONSTANT);

    int start_length = ceil(log10(c->call_start));
    char *start_spaces = int_to_spaces(max_length[3] - start_length + SEPARATOR_CONSTANT);

    int end_length = ceil(log10(c->call_end));
    char *end_spaces = int_to_spaces(max_length[4] - end_length + SEPARATOR_CONSTANT);

    fprintf(f, "%i%s%s%s%s%s%li%s%li%s%li\n",
    c->id,
    id_spaces,
    c->tel,
    tel_spaces,
    c->client_name,
    name_spaces,
    c->call_start,
    start_spaces,
    c->call_end,
    end_spaces,
    c->wait_time
    );

    free(id_spaces);
    free(tel_spaces);
    free(name_spaces);
    free(start_spaces);
    free(end_spaces);
}

int save_calls_to_file(Arguments *arguments, SimResults *results) {
    FILE *f = fopen(arguments->path, "a");

    if (f == NULL) {
        printf(COULD_NOT_OPEN_SAVE_FILE_MESSAGE);
        exit(COULD_NOT_OPEN_SAVE_FILE);
    }

    // Max length of each categories to align the output.
    int max_lengths[] = {7, 10, 11, 10, 8, 14};
    for (int i=0; i< results->calls_current_size; i++) {
        int current_id_size = ceil(log10(results->calls[i]->id));
        if (current_id_size > max_lengths[0]) max_lengths[0] = current_id_size;

        size_t name_length = strlen(results->calls[i]->client_name);
        if (name_length > max_lengths[2]) max_lengths[2] = name_length;

        int current_call_start_size = ceil(log10(results->calls[i]->call_start));
        if (current_call_start_size > max_lengths[3]) max_lengths[3] = current_call_start_size;

        int current_call_end_size = ceil(log10(results->calls[i]->call_end));
        if (current_call_end_size > max_lengths[4]) max_lengths[4] = current_call_end_size;

        int current_call_wait_size = ceil(log10(results->calls[i]->wait_time));
        if (current_call_wait_size > max_lengths[4]) max_lengths[4] = current_call_wait_size;
    }

    char *id_spaces = int_to_spaces(max_lengths[0] - 7 + SEPARATOR_CONSTANT);
    char *tel_spaces = int_to_spaces(max_lengths[1] - 3 + SEPARATOR_CONSTANT);
    char *name_spaces = int_to_spaces(max_lengths[2] - 11 + SEPARATOR_CONSTANT);
    char *start_spaces = int_to_spaces(max_lengths[3] - 10 + SEPARATOR_CONSTANT);
    char *end_spaces = int_to_spaces(max_lengths[4] - 8 + SEPARATOR_CONSTANT);
    fprintf(f, "CALL_ID%sTEL%sCLIENT_NAME%sCALL_START%sCALL_END%sCALL_WAIT_TIME\n",
    id_spaces,
    tel_spaces,
    name_spaces,
    start_spaces,
    end_spaces
    );

    for (int i=0; i < results->calls_current_size; i++) {
        save_call(f, results->calls[i], max_lengths);
    }

    fclose(f);
}
