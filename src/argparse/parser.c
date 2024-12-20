/* 
========================================== PARSER.C ==========================================
This is an Argument Parser. 
It it comprised of a Tokenizer and a Lexer.

It's role is to transform the string arguments inputed by the user when calling the
program and return an Argument struct which contains the parsed arguments.


The parser is designed to be modular. If you want to add another argument:
    1. Add a field to the Argument struct (see argsparse/types.c)
    2. Register the parameter to the parser syntax (see lexer_add_rule_to_syntax())
    3. Write a callback function which actually parses the relevant Tokens (if they need 
       to be parsed) and puts them in the Argument struct.
(Obviously, if the argument's type is not defined, you also need to change the Tokenizer)

The Parser works like this:
    1. Definition of a Syntax (a list of allowed arguments)
    2. Tokenization the String Arguments
    3. Syntax Verification with the Lexer:arg_types we're matching the syntax against the Tokens
    4. Callbacks calls with their relevant Tokens to fill up the Argument struct

Remarks:
    We chose not to use <argp.h> to parse arguments to make the code a little more
    interesting.
========================================== PARSER.C ==========================================
*/

#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include "argparse/tokenizer.h"
#include "argparse/lexer.h"
#include "argparse/callbacks.h"
#include "argparse/types.h"

#define TOKENIZER_ERROR 401
#define LEXER_ERROR 402
#define PARSER_ERROR 403
#define TOKENIZER_ERROR_MESSAGE "[TOKENIZER ERROR] - Something unexpected went wrong!\n"

#define LAMBDA_DEFAULT 0.05
#define OPERATORS_DEFAULT 5
#define NUMBER_OF_DAYS_DEFAULT 1
#define QUEUE_SIZE_DEFAULT 1000
#define MIN_CALL_DURATION_DEFAULT 30 // 30 seconds
#define MAX_CALL_DURATION_DEFAULT 300 // 5 minutes
#define SHIFT_OPENING_DEFAULT 3600*6 // 6 AM
#define SHIFT_CLOSING_DEFAULT 3600*18 // 6 PM
#define PATH_DEFAULT "output.txt"
#define NAMES_PATH_DEFAULT "data/mock_client_names.csv"

// Creates an instance of the Argument class
// with default parameters.
Arguments *parser_create_arguments() {
    Arguments *a = malloc(sizeof(Arguments));

    a->help = 0;
    a->version = 0;
    a->quiet = 0;
    a->lambda = LAMBDA_DEFAULT;
    a->operators = OPERATORS_DEFAULT;
    a->number_of_days = NUMBER_OF_DAYS_DEFAULT; 
    a->queue_size = QUEUE_SIZE_DEFAULT;
    a->min_call_duration = MIN_CALL_DURATION_DEFAULT;
    a->max_call_duration = MAX_CALL_DURATION_DEFAULT;
    a->shift_opening = SHIFT_OPENING_DEFAULT;
    a->shift_closing = SHIFT_CLOSING_DEFAULT;
    a->wants_to_save = 0;
    a->path = &PATH_DEFAULT[0];
    a->include_names = 0;
    a->names_path = NAMES_PATH_DEFAULT;

    return a;
}


// Should not be called outside of this file.
// This is where you add another Syntax rule.
Syntax* _parser_create_syntax() {

    Syntax *syntax = lexer_init_syntax();
    
    Rule *help = lexer_init_rule("help", 'h', 0, NULL, &cb_help);
    lexer_add_rule_to_syntax(syntax, help);

    Rule *version = lexer_init_rule("version", 'v', 0, NULL, &cb_version);
    lexer_add_rule_to_syntax(syntax, version);

    Rule *quiet = lexer_init_rule("quiet", 'q', 0, NULL, &cb_quiet);
    lexer_add_rule_to_syntax(syntax, quiet);

    int lambda_types[] = {INT | FLOAT};
    Rule *lambda = lexer_init_rule("lambda", 'l', 1, lambda_types, &cb_lambda);
    lexer_add_rule_to_syntax(syntax, lambda);

    int operators_types[] = {INT};
    Rule *operators = lexer_init_rule("operators", 'o', 1, operators_types, &cb_operators);
    lexer_add_rule_to_syntax(syntax, operators);

    int number_of_days_types[] = {INT};
    Rule *number_of_days = lexer_init_rule("number-of-days", 'n', 1, number_of_days_types, &cb_number_of_days);
    lexer_add_rule_to_syntax(syntax, number_of_days);

    int queue_size_types[] = {INT};
    Rule *queue_size = lexer_init_rule("queue-size", '\0', 1, queue_size_types, &cb_queue_size); // no abv for this one
    lexer_add_rule_to_syntax(syntax, queue_size);

    int shift_types[] = {DURATION_UNIT, DURATION_UNIT};
    Rule *shift = lexer_init_rule("shift", 's', 2, shift_types, &cb_shift);
    lexer_add_rule_to_syntax(syntax, shift);

    int duration_types[] = {DURATION_UNIT, DURATION_UNIT};
    Rule *duration = lexer_init_rule("duration", 'd', 2, duration_types, &cb_duration);
    lexer_add_rule_to_syntax(syntax, duration);

    int output_file_types[] = {STRING};
    Rule *output_file = lexer_init_rule("output-file", '\0', 1, output_file_types, &cb_output_file);
    lexer_add_rule_to_syntax(syntax, output_file);

    int include_names_types[] = {STRING};
    Rule *include_names = lexer_init_rule("include-names", '\0', 1, include_names_types, &cb_include_names);
    lexer_add_rule_to_syntax(syntax, include_names);

    return syntax;

}


// Parses the string arguments and puts them into an Arguments struct.
int parser_parse_args(int argc, char *argv[], Arguments *arguments) {

    int number_of_tokens = 0;
    Token *tokens = tokenizer_tokenize(argc, argv, &number_of_tokens);

    Syntax *syntax = _parser_create_syntax();

    lexer_get_arguments(syntax, tokens, arguments, number_of_tokens);

    return 0;
}