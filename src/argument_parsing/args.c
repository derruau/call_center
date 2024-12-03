/* 

This is an argument parser. 
It it comprised of a Tokenizer, a Lexer and a Parser.

We chose not to use <argp.h> to parse arguments to make the code 
a little more interesting.

*/

#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include "../../include/tokenizer.h"
#include "../../include/lexer.h"

#define TOKENIZER_ERROR 401
#define LEXER_ERROR 402
#define PARSER_ERROR 403
#define TOKENIZER_ERROR_MESSAGE "[TOKENIZER ERROR] - Something unexpected went wrong!\n"

//TODO: Setup good values for the defaults
#define LAMBDA_DEFAULT 1.2
#define OPERATORS_DEFAULT 5
#define MINSRV_DEFAULT 2
#define MAXSRV_DEFAULT 12
#define SHIFT_OPENING_DEFAULT 155
#define SHIFT_CLOSING_DEFAULT 4666
#define PATH_DEFAULT "output.txt"

typedef struct s_arguments{
    int help;
    int version;
    float lambda;
    float operators;

    // Corresponds to the -d argument
    time_t minsrv;
    time_t maxsrv;

    // Corresponds to the -s argument
    time_t shift_opening;
    time_t shift_closing;

    char *path;
} Arguments;

Arguments *args_create_arguments() {
    Arguments *a = malloc(sizeof(Arguments));

    a->help = 0;
    a->version = 0;
    a->lambda = LAMBDA_DEFAULT;
    a->operators = OPERATORS_DEFAULT;
    a->minsrv = MINSRV_DEFAULT;
    a->maxsrv = MAXSRV_DEFAULT;
    a->shift_opening = SHIFT_OPENING_DEFAULT;
    a->shift_closing = SHIFT_CLOSING_DEFAULT;
    a->path = &PATH_DEFAULT[0];

    return a;
}

Syntax* _args_create_syntax() {

    Syntax *syntax = lexer_init_syntax();
    
    Expression *help = lexer_init_expression("help", 'h', 0, NULL);
    lexer_add_expression_to_syntax(syntax, help);

    Expression *version = lexer_init_expression("version", 'v', 0, NULL);
    lexer_add_expression_to_syntax(syntax, version);

    int lambda_types[] = {INT | FLOAT};
    Expression *lambda = lexer_init_expression("lambda", 'l', 1, lambda_types);
    lexer_add_expression_to_syntax(syntax, lambda);

    int shift_types[] = {DURATION_UNIT, DURATION_UNIT};
    Expression *shift = lexer_init_expression("shift", 's', 2, shift_types);
    lexer_add_expression_to_syntax(syntax, lambda);

    int duration_types[] = {DURATION_UNIT, DURATION_UNIT};
    Expression *duration = lexer_init_expression("duration", 'd', 2, duration_types);
    lexer_add_expression_to_syntax(syntax, duration);

    int number_of_days_types[] = {INT};
    Expression *number_of_days = lexer_init_expression("number-of-days", 'n', 1, number_of_days_types);
    lexer_add_expression_to_syntax(syntax, number_of_days);

    int operators_types[] = {INT};
    Expression *operators =lexer_init_expression("operators", 'o', 1, operators_types);
    lexer_add_expression_to_syntax(syntax, operators);

    return syntax;

}

int args_handle(int argc, char *argv[], Arguments *arguments) {
    // If returns anything other than 0, it failed

    Token *tokens;
    int number_of_tokens = tokenizer_tokenize(argc, argv, tokens);

    Syntax *syntax = _args_create_syntax();

    lexer_get_arguments(syntax, tokens, arguments, number_of_tokens);

    return 0;
}