#include "../include/helper.h"
#include"../include/simulation.h"
#include <stdlib.h>
#include <stdio.h>
#include "../include/args.h"
//#include "../include/call.h"
// #define lambda 1
// #define minsrv 2 // debut du service 
// #define maxsrv 5 // fin du service 
// #define op_number 5

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

    Call **c;
    c=call_create_n_random(10, a->shift_opening, a->shift_closing, a->lambda, a->minsrv, a->maxsrv);

    //for (int i=0; i<10; i++) {
    //    helper_print_call(c[i]);
    //}

    Queue *q = queue_init(3);
    time_t begin, end;
    time(&begin);
    end=begin+60*30;
    int v1 = 1;
    int v2 = 2;
    int v3 = 3;
    int v4 = 4;
    simulation_register(c,  10);

}
