#include "../include/call.h"
#include "../include/queue.h"
#include "../include/helper.h"
#include "../include/args.h"
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char *argv[]) {

    Arguments *a = args_create_arguments();
    int arg_parsing_error = args_handle(argc, argv, a);

    helper_print_arguments(a);

}