/*

Lexer.c
    Checks the syntax of the tokens and converts them to a parse tree 

Syntax:
    - Tree: [EXPRESSION]* Path(String)
    - EXPRESSION: [OPTION] | [PARAMETER]
    - OPTION: atom <-- Option = Parameter avec 0 VALUES DERRIERE
    - PARAMETER: [FLAG] [VALUE]+

Architecture:
    - Definition of the options & parameters at runtime
    - 
*/

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>
#include "../../include/arg_types.h"


#define CANNOT_ADD_SYNTAX_ERROR 421
#define FLAG_NOT_IN_SYNTAX 422
#define BAD_SYNTAX_ERROR 423
#define CANNOT_ADD_SYNTAX_ERROR_MESSAGE "[LEXER ERROR] - Cannot add another expression to the syntax!\n"
#define FLAG_NOT_IN_SYNTAX_MESSAGE "[LEXER ERROR] - Flag is not in the syntax!\n"
#define BAD_SYNTAX_ERROR_MESSAGE "[LEXER ERROR] - Syntax error!\n"

#define SYNTAX_SIZE_INCREASE 5

// Forward declarations 
typedef struct s_arguments Arguments;
struct s_tokens;

Syntax *lexer_init_syntax() {
    Syntax *s = malloc(sizeof(Syntax));

    s->current_size = 0;
    s->max_size = 1;

    return s;
}

Expression *lexer_init_expression(char *full_name, char abv, int param_number, int param_type[], lexer_callback cb) {
    Expression *e = malloc(sizeof(Expression) + param_number*sizeof(Expression));

    e->full_name = full_name;
    e->has_abv = abv == '\0' ? 0 : 1;
    if (e->has_abv) e->abv = abv;
    e->param_number = param_number;
    
    for (int i=0; i < param_number; i++) {
        e->param_type[i] = param_type[i];
    }

    e->cb = cb;

    return e;
}

int lexer_add_expression_to_syntax(Syntax *syntax, Expression *expression ) {
    if (syntax->current_size == syntax->max_size) {
        int new_size = sizeof(Syntax) + (syntax->max_size + SYNTAX_SIZE_INCREASE)*sizeof(Expression*);
        Syntax *ns = realloc(syntax, new_size);
        if (ns == NULL) {
            printf(CANNOT_ADD_SYNTAX_ERROR_MESSAGE);
            exit(CANNOT_ADD_SYNTAX_ERROR);
        }
        syntax = ns;
        syntax->max_size = new_size;
    }

    syntax->s[syntax->current_size] = expression;
    syntax->current_size++;

    return 0;

}



Expression *_lexer_get_expression_from_flag_name(Syntax *syntax, char* name) {
    for (int i=0; i<syntax->current_size; i++) {
        if (strcmp(syntax->s[i]->full_name, name) == 0) {
            return syntax->s[i];
        }
    }
    printf(FLAG_NOT_IN_SYNTAX_MESSAGE);
    exit(FLAG_NOT_IN_SYNTAX);
}

int lexer_get_arguments(Syntax *syntax, Token *tokens, Arguments *arguments, int tokens_size) {
    // If returns anything other than 0, it failed!


    int i=0;
    while (i < tokens_size) {
        if (tokens[i].type == FLAG) {
            Expression *e = _lexer_get_expression_from_flag_name(syntax, tokens[i].data.f->name);
            // RAJOUTER LE CALLBACK DANS lexer_init_expression!!
            // Aussi la définition du callback est nulle, ce serait mieux de renvoyer directement 
            // un pointeur vers les tokens des arguments correspondants!!
            Token **relevant_tokens = malloc(sizeof(Token*)*e->param_number);

            for (int i=0; i<e->param_number; i++) {
                if (i + 1 >= tokens_size || tokens[i + 1].type != VALUE)  {
                    printf(BAD_SYNTAX_ERROR_MESSAGE);
                    exit(BAD_SYNTAX_ERROR);
                }
                // If the token has a valid data type 
                if (e->param_type[0] & tokens[i + 1].data.v->type != 0) {
                    relevant_tokens[i] = &tokens[i];
                }
            }

            // Calling the callback
            e->cb(arguments, relevant_tokens);
        }

        i++;
    }
}

