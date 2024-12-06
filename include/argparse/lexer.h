#ifndef LEXER
#define LEXER

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "types.h"

Syntax *lexer_init_syntax();

Rule *lexer_init_rule(char *full_name, char abv, int number_of_values, int value_type[], lexer_callback cb);

int lexer_add_rule_to_syntax(Syntax *syntax, Rule *rule );

int lexer_get_arguments(Syntax *syntax, Token *tokens, Arguments *arguments, int number_of_tokens);

#endif