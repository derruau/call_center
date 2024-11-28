/*

Tokenizer:
    Uhhh...

*/

#include <stdio.h>
#include <stdlib.h>
#include <regex.h>

#define REGEX_COMPILATION_ERROR 411
#define BAD_TOKEN_ERROR 412
#define CANT_TOKENIZE_DURATION_UNIT 413
#define REGEX_COMPILATION_ERROR_MESSAGE "[TOKENIZER ERROR] - Could not compile argument parsing regex!\n"
#define BAD_TOKEN_ERROR_MESSAGE "[USER ERROR] - Bad argument syntax!\n"
#define CANT_TOKENIZE_DURATION_UNIT_MESSAGE "[TOKENIZER ERROR] - Could not tokenize a duration!\n"
#define TOKENIZER_GENERAL_ERROR 410


#define FLAG_REGEX "(^-[a-z]$)|(^--[a-z](([a-z])|(-)){1,}$)"
#define INT_REGEX "^-?[0-9]+$"
#define FLOAT_REGEX "^-?[0-9]+\\.[0-9]+$"
#define DURATION_REGEX "^[0-9]+[smhdwMy]:[0-9]+[smhdwMy]$"
#define STRING_REGEX "^(\\w| )+$"


typedef enum _e_value_type {
    INT,
    FLOAT,
    DURATION,
    DURATION_UNIT,
    STRING,
} _value_type;

typedef enum e_token_type {
    FLAG,
    VALUE
} _token_type;

struct _s_flag {
    char *name;
};

struct _s_value {
    void *data;
    _value_type type;
};

typedef union _u_token {
    struct _s_flag* f;
    struct _s_value* v;
} _token;

typedef struct s_token {
    _token_type type;
    _token data;
} Token;


void tokenizer_print_token(Token token) {
    
}

int _tokenizer_handle_duration(char *argv, Token *tokens, int tokens_pos) {
    int i = 0;
    char c = argv[0];
    int cs_size = sizeof(char);
    char *current_string = malloc(cs_size);
    while (c != '\0') {
        if (c == ':') {
            tokens[tokens_pos].type = VALUE;
            struct _s_value s = {(void*) current_string, DURATION_UNIT};
            tokens[tokens_pos].data.v = &s;

            // New string
            cs_size = sizeof(char);
            current_string = malloc(cs_size);

            i++;
            c = argv[i];
            continue;
        }

        current_string[i] = c;

        cs_size += sizeof(char);
        char *new_current_string = realloc(current_string, cs_size);
        if (new_current_string == NULL) {
            printf(CANT_TOKENIZE_DURATION_UNIT_MESSAGE);
            exit(CANT_TOKENIZE_DURATION_UNIT);
        }
        current_string = new_current_string;

        i++;
        c = argv[i];
    }
    tokens[tokens_pos + 1].type = VALUE;
    struct _s_value s = {(void*) current_string, DURATION_UNIT};
    tokens[tokens_pos + 1].data.v = &s;


    return 2;
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
        char *s = argv[pos][1] == '-' ? &argv[pos][2]: &argv[pos][1];
        
        tokens[pos - 1].type = FLAG;
        tokens[pos - 1].data.f = (struct _s_flag*) {(void*) s};
        return 1;
    }

    if (number_result == 0) { // argv is a number
        int val = atoi(argv[pos]);
        struct _s_value s = {(void*) &val, INT};

        tokens[pos - 1].type = VALUE;
        tokens[pos - 1].data.v = &s;
        return 1;
    }

    if (number_result == 0) { // argv is a floating point number
        float val = (float) atof(argv[pos]);
        struct _s_value s = {(void*) &val, INT};

        tokens[pos - 1].type = VALUE;
        tokens[pos - 1].data.v = &s;
        return 1;
    }

    if (duration_result == 0) { //argv is a duration
        // return _tokenizer_handle_duration(argv[pos], tokens, pos + 1);
        return 2;
    }

    if (string_result == 0) { //argv is a string
        struct _s_value s = {(void*) argv[pos], STRING};

        tokens[pos - 1].type = VALUE;
        tokens[pos - 1].data.v = &s;
        return 1;
    }

    else {
        printf(BAD_TOKEN_ERROR_MESSAGE);
        exit(BAD_TOKEN_ERROR);
    }
    
}

int tokenizer_tokenize(int argc, char *argv[], Token *tokens) {
    if (argc < 1) return TOKENIZER_GENERAL_ERROR;

    // Two times the argc value is the maximum
    // number of tokens we can have because the worst
    // case scenario is every string in argv is a duration
    // which splits into two value tokens.
    tokens = malloc(sizeof(Token)*(argc - 1)*2);

    // Test pour set un token:
    struct _s_flag a = {"bruh"};
    tokens[0].type = FLAG;
    tokens[0].data.f = (struct _s_flag*) &a;

    int i = 1;
    while (i < argc) { 
        i += _tokenizer_process_argv(argv, tokens, i);
    }

    //truncate Tokens to it actual size
    tokens = realloc(tokens,sizeof(Token)*i);
    if (tokens == NULL) {
        return TOKENIZER_GENERAL_ERROR;
    }

    return 0;
}