#include "../include/call.h"
#include "../include/queue.h"
#include "../include/helper.h"
#include "../include/args.h"
#include <stdlib.h>
#include <stdio.h>

//TODO: add documentation to the code
//TODO: Make the functions have a more consistent style
//TODO: standardize the name of the function's arguments
int main(int argc, char *argv[]) {

    // Parses the arguments into 'a'. If you wish to see
    // The structure of Arguments, please refer to
    // argument_parsing/arg_types.c
    Arguments *a = args_create_arguments();
    int arg_parsing_error = args_handle(argc, argv, a);

    helper_print_arguments(a);

}