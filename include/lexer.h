#ifndef LEXER
#define LEXER

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "tokenizer.h"


// Forward declaration
typedef struct s_arguments Arguments;
struct s_tokens;

typedef void (*lexer_callback)(struct s_arguments *a, struct s_tokens *t, int tokens_size); 

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
    Expression **s;
} Syntax;

Syntax *lexer_init_syntax();

Expression *lexer_init_expression(char *full_name, char abv, int param_number, int param_type[]);

int lexer_add_expression_to_syntax(Syntax *syntax, Expression *expression );

int lexer_get_arguments(Syntax *syntax, Token *tokens, Arguments *arguments, int tokens_size);

#endif