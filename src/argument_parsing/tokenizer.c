/*

Tokenizer:
    Uhhh...

*/

#include <stdio.h>
#include <stdlib.h>
#include <regex.h>
#include "../../include/arg_types.h"
#include "../../include/helper.h"


#define TOKENIZER_GENERAL_ERROR 410
#define REGEX_COMPILATION_ERROR 411
#define BAD_TOKEN_ERROR 412
#define CANT_TOKENIZE_DURATION_UNIT 413
#define BAD_TOKEN_TYPE 414
#define REGEX_COMPILATION_ERROR_MESSAGE "[TOKENIZER ERROR] - Could not compile argument parsing regex!\n"
#define BAD_TOKEN_ERROR_MESSAGE "[USER ERROR] - Bad arguments!\n"
#define CANT_TOKENIZE_DURATION_UNIT_MESSAGE "[TOKENIZER ERROR] - Could not tokenize a duration!\n"
#define BAD_TOKEN_TYPE_MESSAGE "[TOKENIZER ERROR] - Token type not recognised!"


#define FLAG_REGEX "(^-[a-z]$)|(^--[a-z](([a-z])|(-)){1,}$)"
#define INT_REGEX "^-?[0-9]+$"
#define FLOAT_REGEX "^-?[0-9]+\\.[0-9]+$"
#define DURATION_REGEX "^[0-9]+[smhdwMy]:[0-9]+[smhdwMy]$"
#define STRING_REGEX "^(\\w| |.)+$"


char *_tokenizer_get_substring_of(char *s, int start_pos) {
    char *result = malloc(sizeof(char)*20);
    int malloc_size = 1;
    int i = start_pos;
    while (s[i] != '\0') {
        result[i-start_pos] = s[i];
        char* new_result = realloc(result, sizeof(char)*(malloc_size+1));
        if (new_result == NULL) {
            printf("[TOKENIZER ERROR] - Memory allocation failed!\n");
            exit(TOKENIZER_GENERAL_ERROR);
        }
        result = new_result;

        i++;
        malloc_size++;
    }

    result[i-start_pos] = '\0';

    return result;
}

void tokenizer_print_token(Token token) {
    if (token.type == FLAG) {
        if (token.data.f == 0) return;
        printf("Token{ type: FLAG, name: %s}\n", (char*)token.data.f->name);
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
    } else {
        printf(BAD_TOKEN_TYPE_MESSAGE);
        exit(BAD_TOKEN_TYPE);
    }
}

int _tokenizer_handle_duration(char *argv, Token *tokens, int tokens_pos) {
    char **strings = malloc(sizeof(char*)*2);
    int current_string = 0;

    int i = 0;
    int si = 0;
    strings[current_string] = malloc(sizeof(char));
    char c = argv[i];
    while (c != '\0') {
        if (c == ':') {
            strings[current_string][i] = '\0';

            //Initialization of end duration n°2
            current_string++;
            strings[current_string] = malloc(sizeof(char));
            
            i++;
            si = 0;
            c = argv[i];
            continue;
        }

        strings[current_string][si] = c;

        char *ns = realloc(strings[current_string], sizeof(char)*(si +1));
        if (ns == NULL) {
            printf(CANT_TOKENIZE_DURATION_UNIT_MESSAGE);
            exit(CANT_TOKENIZE_DURATION_UNIT);
        }
        strings[current_string] = ns;

        i++;
        si++;
        c = argv[i];
    }

    struct _s_value *s1 = malloc(sizeof(struct _s_value));
    s1->data = (void*) strings[0];
    s1->type = DURATION_UNIT;
    tokens[tokens_pos].type = VALUE;
    tokens[tokens_pos].data.v = s1;

    strings[current_string][si] = '\0';
    struct _s_value *s2 = malloc(sizeof(struct _s_value));
    s2->data = (void*) strings[1];
    s2->type = DURATION_UNIT;
    tokens[tokens_pos + 1].type = VALUE;
    tokens[tokens_pos + 1].data.v = s2;

    return 0;
}

int _tokenizer_process_argv(char *argv[], Token *tokens, int pos) {
    regex_t flag;
    regex_t number;
    regex_t floating_point;
    regex_t duration;
    regex_t string;

    if (
        regcomp(&flag, FLAG_REGEX, REG_EXTENDED)            ||
        regcomp(&number, INT_REGEX, REG_EXTENDED)           ||
        regcomp(&duration, DURATION_REGEX, REG_EXTENDED)    ||
        regcomp(&floating_point, FLOAT_REGEX, REG_EXTENDED) ||
        regcomp(&string, STRING_REGEX, REG_EXTENDED)
        ) {
        printf(REGEX_COMPILATION_ERROR_MESSAGE);
        exit(REGEX_COMPILATION_ERROR);
    }

    // regexec returns 0 when successful
    int flag_result = regexec(&flag, argv[pos], 0, NULL, 0);
    int number_result = regexec(&number, argv[pos], 0, NULL, 0);
    int floating_point_result = regexec(&floating_point, argv[pos], 0, NULL, 0);
    int duration_result = regexec(&duration, argv[pos], 0, NULL, 0);
    int string_result = regexec(&string, argv[pos], 0, NULL, 0);

    if (flag_result == 0) { // argv is a flag
        int start_pos = argv[pos][1] == '-' ? 2 : 1;
        char *s = _tokenizer_get_substring_of(argv[pos], start_pos);
        struct _s_flag *ts = malloc(sizeof(struct _s_flag));
        ts->name = s;
        
        tokens[pos - 1].type = FLAG;
        tokens[pos - 1].data.f = ts;

        return 1;
    }

    if (number_result == 0) { // argv is a number
        int *val = malloc(sizeof(int));
        *val = atoi(argv[pos]);
        struct _s_value *s = malloc(sizeof(struct _s_value));
        s->type = INT;
        s->data = (void*) val;

        tokens[pos - 1].type = VALUE;
        tokens[pos - 1].data.v = s;

        return 1;
    }

    if (floating_point_result == 0) { // argv is a floating point number
        float *val = malloc(sizeof(float));
        *val = (float)atof(argv[pos]);
        struct _s_value *s = malloc(sizeof(struct _s_value));
        s->data = (void*) val;
        s->type =FLOAT;

        tokens[pos - 1].type = VALUE;
        tokens[pos - 1].data.v = s;

        return 1;
    }

    if (duration_result == 0) { //argv is a duration
        _tokenizer_handle_duration(argv[pos], tokens, pos -1);

        return 2;
    }

    if (string_result == 0) { //argv is a string
        struct _s_value *s = malloc(sizeof(struct _s_value));
        s->data = (void*) argv[pos];
        s->type = STRING;

        tokens[pos - 1].type = VALUE;
        tokens[pos - 1].data.v = s;

        return 1;
    }

    else {
        printf(BAD_TOKEN_ERROR_MESSAGE);
        exit(BAD_TOKEN_ERROR);
    }
    
}

Token *tokenizer_tokenize(int argc, char *argv[], int *number_of_tokens) {
    if (argc < 1) exit(TOKENIZER_GENERAL_ERROR);

    // Two times the argc value is the maximum
    // number of tokens we can have because the worst
    // case scenario is every string in argv is a duration
    // which splits into two value tokens.
    Token *tokens = malloc(sizeof(Token)*(argc - 1)*2);

    int i = 1;
    while (i < argc) { 
        i += _tokenizer_process_argv(argv, tokens, i);
    }

    //truncate Tokens to it actual size
    tokens = realloc(tokens,sizeof(Token)*i);
    if (tokens == NULL) {
        exit(TOKENIZER_GENERAL_ERROR);
    }

    *number_of_tokens = i - 1;
    return tokens;
}