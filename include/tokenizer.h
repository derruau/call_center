#ifndef TOKENIZER
#define TOKENIZER


typedef enum _e_value_type {
    INT,
    FLOAT,
    DURATION,
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
    struct _s_flag f;
    struct _s_value v;
} _token;

typedef struct s_token {
    _token_type type;
    _token data;
} Token;

int tokenizer_tokenize(int argc, char *argv[], Token *tokens);

#endif