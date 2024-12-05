#include "../include/helper.h"
#include "../include/args.h"
#include "../include/call.h"

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

    Call **c = call_create_n_random(10, a->shift_opening, a->shift_closing, a->lambda, a->minsrv, a->maxsrv);

    for (int i=0; i<10; i++) {
        helper_print_call(c[i]);
    }

    return 0;

}