#ifndef ARG_TYPES
#define ARG_TYPES

#include <time.h>

//================ tokenizer.c types ================


typedef enum _e_value_type {
    INT = 0b00001,
    FLOAT = 0b00010,
    DURATION = 0b00100,
    DURATION_UNIT = 0b01000,
    STRING = 0b10000,
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

//================ args.c types ================

typedef struct s_arguments{
    int help;
    int version;
    float lambda;
    float operators;
    int number_of_days;

    // Corresponds to the -d argument
    time_t minsrv;
    time_t maxsrv;

    // Corresponds to the -s argument
    time_t shift_opening;
    time_t shift_closing;

    char *path;
} Arguments;

//================ lexer.c types ================

typedef void (*lexer_callback)(Arguments *a, Token **t); 

typedef struct {
    char abv;
    int has_abv;
    char *full_name;
    
    //Callback to when there is a match in tokens
    lexer_callback cb;

    // Number of value tokens after the flag
    int param_number;
    // Type of each Value Parameter. A parameter can be of multiple types,
    // so each int is the Bitwise-OR of all the types he can be
    // For example: if the parameter can be a FLOAT or an INT the Value will be
    // equal to FLOAT | INT
    int param_type[];
} Expression;

typedef struct {
    int max_size;
    int current_size;
    // A hash table would be better because that would mean
    // instant access time but with small syntax size it's fine.
    Expression **s;
} Syntax;


#endif