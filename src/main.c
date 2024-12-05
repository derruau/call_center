#include "../include/call.h"
#include "../include/queue.h"
#include "../include/helper.h"
#include"../include/simulation.h"
#include <stdlib.h>
#include <stdio.h>
#define lambda 1
#define minsrv 2 // debut du service 
#define maxsrv 5 // fin du service 
#define op_number 5

int main() {
    Queue *q = queue_init(3);
    time_t begin, end;
    time(&begin);
    end=begin+60*30;
    int v1 = 1;
    int v2 = 2;
    int v3 = 3;
    int v4 = 4;

    queue_enqueue(q, &v1);
    queue_enqueue(q, &v2);
    queue_enqueue(q, &v3);
    
    queue_dequeue(q);
    queue_dequeue(q);
    queue_enqueue(q, &v4);

    helper_print_int_queue(q);

    helper_get_random_name_from_file("data/mock_client_names.csv");
    Call *clients=call_create_n_random(5,begin, end, lambda, minsrv, maxsrv);
    start_simulation(&clients, 5);
    //TODO: test functions in call.c

}