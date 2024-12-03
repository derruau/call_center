#ifndef TOKENIZER
#define TOKENIZER

#include "arg_types.h"

void tokenizer_print_token(Token token);

int tokenizer_tokenize(int argc, char *argv[], Token *tokens);

#endif