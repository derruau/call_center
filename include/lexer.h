#ifndef LEXER
#define LEXER

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "arg_types.h"

Syntax *lexer_init_syntax();

Expression *lexer_init_expression(char *full_name, char abv, int param_number, int param_type[], lexer_callback cb);

int lexer_add_expression_to_syntax(Syntax *syntax, Expression *expression );

int lexer_get_arguments(Syntax *syntax, Token *tokens, Arguments *arguments, int tokens_size);

#endif