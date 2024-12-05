#ifndef LEXER
#define LEXER

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "arg_types.h"

Syntax *lexer_init_syntax();

Rule *lexer_init_rule(char *full_name, char abv, int param_number, int param_type[], lexer_callback cb);

int lexer_add_rule_to_syntax(Syntax *syntax, Rule *expression );

int lexer_get_arguments(Syntax *syntax, Token *tokens, Arguments *arguments, int tokens_size);

#endif