#ifndef TOKENIZER
#define TOKENIZER

#include "types.h"

void tokenizer_print_token(Token token);

Token *tokenizer_tokenize(int argc, char *argv[], int *number_of_tokens);

#endif