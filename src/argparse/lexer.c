/* 
========================================== LEXER.C ==========================================
This file matches the Tokens against the Syntax and passes relevant Tokens to each 
callback functions.

If you don't know what a Lexer is:
    A Lexer is part of a Parser. It takes a list of Token as an input and will try to make
    sense of them. For example with the string '3 + 5' from the Tokenizer's header 
    comment, the input will be [ ['3', number] , ['+', operator ], ['5', number] ].
    The Lexer will read all three Tokens and conclude that they mean to represent the addition
    of 3 and 5. It will represent this meaning in a special structure called an Abstract Syntax
    Tree and pass this tree to the next component of the Parser: The Parser.

    In this program, we don't need a Syntax Tree nor a Parser, so this explanation is somewhat
    useless but it's cool to learn about Parser Theory.



For definitions and explanations about Rules and Syntax, please see arg_types.c's header
comment.

The General Syntax that this parser matches is the following (in Regex notation):
                            [Rule]* [STRING]
With a Rule being defined like this: 
                            [FLAG] [VALUE]*

The [STRING] at the end of the Syntax is the path that the simulation result will be saved to.
It is a special Syntax qwirk that isn't defined in a Rule but is hardcoded in lexer_get_arguments().

Remarks:
    To be able to define this qwirk in a Rule, I would have to introduce some kind of position
    sensitive syntax system (which I don't have the time to do right now) or otherwise make a
    fully fledged parser with an AST. 
========================================== LEXER.C ==========================================
*/

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>
#include "argparse/types.h"


#define CANNOT_ADD_SYNTAX_ERROR 421
#define FLAG_NOT_IN_SYNTAX 422
#define BAD_SYNTAX_ERROR 423
#define CANNOT_ADD_SYNTAX_ERROR_MESSAGE "[LEXER ERROR] - Cannot add another expression to the syntax!\n"
#define FLAG_NOT_IN_SYNTAX_MESSAGE "[LEXER ERROR] - Flag is not in the syntax!\n"
#define BAD_SYNTAX_ERROR_MESSAGE "[LEXER ERROR] - Syntax error!\n"

#define SYNTAX_SIZE_INCREASE 5

// Retuns a new Syntax struct with default 
// values filled in.
// See arg_types.c for explanations about what is a Syntax
Syntax *lexer_init_syntax() {
    Syntax *s = malloc(sizeof(Syntax));

    s->current_size = 0;
    s->max_size = 1;

    s->s = malloc(sizeof(Rule*)*s->max_size);

    return s;
}

//TODO: rename parameters for better consistency
// Returns a new Rule with the parameters you've passed it
// See arg_types.c for explanations about what is a Rule
Rule *lexer_init_rule(char *full_name, char abv, int param_number, int param_type[], lexer_callback cb) {
    Rule *e = malloc(sizeof(Rule) + param_number*sizeof(Rule));

    e->full_name = full_name;
    e->has_abv = abv == '\0' ? 0 : 1;
    if (e->has_abv) e->abv = abv;
    e->number_of_values = param_number;
    
    for (int i=0; i < param_number; i++) {
        e->values_type[i] = param_type[i];
    }

    e->cb = cb;

    return e;
}

// Adds a Rule to the Syntax
// See arg_types.c for explanations about what is a Rule / Syntax
int lexer_add_rule_to_syntax(Syntax *syntax, Rule *expression ) {
    if (syntax->current_size <= syntax->max_size) {
        int new_size = (syntax->max_size + SYNTAX_SIZE_INCREASE)*sizeof(Rule*);
        Rule **ns = realloc(syntax->s, new_size);
        if (ns == NULL) {
            printf(CANNOT_ADD_SYNTAX_ERROR_MESSAGE);
            exit(CANNOT_ADD_SYNTAX_ERROR);
        }
        syntax->s = ns;
        syntax->max_size += SYNTAX_SIZE_INCREASE;
    }

    syntax->s[syntax->current_size] = expression;
    syntax->current_size++;

    return 0;

}


// Should not be used outside this file
// Searches a Rule in the Syntax and returns the first
// Rule that matches the name provided
Rule *_lexer_get_rule_from_flag_name(Syntax *syntax, char* name) {
    for (int i=0; i<syntax->current_size; i++) {
        if (strcmp(syntax->s[i]->full_name, name) == 0) {
            return syntax->s[i];
        }

        if (syntax->s[i]->has_abv == 0) continue;
        if (syntax->s[i]->abv == name[0]) {
            return syntax->s[i];
        }
    }
    printf(FLAG_NOT_IN_SYNTAX_MESSAGE);
    exit(FLAG_NOT_IN_SYNTAX);
}

//TODO: rename parameters for better consistency
// The main Lexer function.
// Checks the Tokens against the Syntax and fills up
// the Arguments struct with the relevant informations
int lexer_get_arguments(Syntax *syntax, Token *tokens, Arguments *arguments, int tokens_size) {

    int i=0;
    while (i < tokens_size) {
        // Special case for the last token (i.e the path)
        if (i == tokens_size - 1) {
            if (tokens[i].type == VALUE) {
                if (tokens[i].data.v->type == STRING) {
                    arguments->path = (char*)tokens[i].data.v->data;
                    return 0;
                }
            } 
        }

        if (tokens[i].type == FLAG) {
            Rule *e = _lexer_get_rule_from_flag_name(syntax, tokens[i].data.f->name);
            Token **relevant_tokens = malloc(sizeof(Token*)*e->number_of_values);

            for (int j = 0; j < e->number_of_values; j++) {
                if (i + j + 1 >= tokens_size || tokens[i + j + 1].type != VALUE)  {
                    printf(BAD_SYNTAX_ERROR_MESSAGE);
                    exit(BAD_SYNTAX_ERROR);
                }
                // If the token has a valid data type 
                if (e->values_type[j] & tokens[i + j + 1].data.v->type) {
                    relevant_tokens[j] = &tokens[i + j +1];
                } else {
                    printf(BAD_SYNTAX_ERROR_MESSAGE);
                    exit(BAD_SYNTAX_ERROR);
                }
            }

            // Calling the callback
            e->cb(arguments, relevant_tokens);

            i += e->number_of_values + 1;
            continue;
        }

        printf(BAD_SYNTAX_ERROR_MESSAGE);
        exit(BAD_SYNTAX_ERROR);
    }
}

