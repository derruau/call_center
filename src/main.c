#include "../include/call.h"
#include "../include/queue.h"
#include "../include/helper.h"
#include "../include/args.h"
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char *argv[]) {

    Arguments *a = args_create_arguments();
    int arg_parsing_error = args_handle(argc, argv, a);

    // Queue *q = queue_init(3);

    // int v1 = 1;
    // int v2 = 2;
    // int v3 = 3;
    // int v4 = 4;

    // queue_enqueue(q, &v1);
    // queue_enqueue(q, &v2);
    // queue_enqueue(q, &v3);
    
    // queue_dequeue(q);
    // queue_dequeue(q);
    // queue_enqueue(q, &v4);

    // helper_print_int_queue(q);

    // helper_get_random_name_from_file("data/mock_client_names.csv");

    //TODO: test functions in call.c

}