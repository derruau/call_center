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
#include "../../include/tokenizer.h"

#define CANNOT_ADD_SYNTAX_ERROR 421
#define CANNOT_ADD_SYNTAX_ERROR_MESSAGE "[LEXER ERROR] - Cannot add another expression to the syntax!\n"

#define SYNTAX_SIZE_INCREASE 5

// Forward declarations 
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

Syntax *lexer_init_syntax() {
    Syntax *s = malloc(sizeof(Syntax));

    s->current_size = 0;
    s->max_size = 1;

    return s;
}

Expression *lexer_init_expression(char *full_name, char abv, int param_number, int param_type[]) {
    Expression *e = malloc(sizeof(Expression) + param_number*sizeof(Expression));

    e->full_name = full_name;
    e->has_abv = abv == '\0' ? 0 : 1;
    if (e->has_abv) e->abv = abv;
    e->param_number = param_number;
    
    for (int i=0; i < param_number; i++) {
        e->param_type[i] = param_type[i];
    }

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

int lexer_get_arguments(Syntax *syntax, Token *tokens, Arguments *arguments, int tokens_size) {
    // Modifier le tokenizer pour qu'il renvoie le nombre de tokens + le passer en argument de cette fct
    // Aussi tester le code ça pourrait être bien...
}

