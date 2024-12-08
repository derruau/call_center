/* 
========================================== SIMULATION.C ==========================================
This file's role is to perform the simulation

The simulation wor


architecture:
    functions:
        - simulate_day()
        - simulate_n_days()
    structs:
        - stats --> see docs/consigne.pdf
        - sim_results: {calls **c, stats *s, int has_stats}

========================================== SIMULATION.C ==========================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "sim/types.h"
#include "argparse/types.h"
#include "sim/misc.h"
#include "sim/queue.h"
#include "sim/call.h"
#include "sim/stats.h"

#define SIZE_OF_CALL_QUEUE 20

#define OPERATOR_NUMBER_IS_NEGATIVE 501
#define OPERATOR_ALREADY_OCCUPIED 502
#define COULDNT_ALLOCATE_MEMORY 503
#define CALL_QUEUE_IS_FULL 504
#define OPERATOR_NUMBER_IS_NEGATIVE_MESSAGE "[SIMULATION ERROR] - Operator number must be positive!\n"
#define OPERATOR_ALREADY_OCCUPIED_MESSAGE "[SIMULATION ERROR] - Operator is already occupied!\n"
#define COULDNT_ALLOCATE_MEMORY_MESSAGE "[SIMULATION ERROR] - Couldn't allocate more memory to program!\n"
#define CALL_QUEUE_IS_FULL_MESSAGE "[SIMULATION ERROR] - Call Queue is full!\n"

Operator *sim_create_operator(time_t ends_in) {
    Operator *o = malloc(sizeof(Operator));

    if (ends_in >= 0) {
        o->occupied = 1;
        o->ends_in = ends_in;
        return o;
    }

    o->occupied = 0;
    o->ends_in = -1;
    return o;
}

Operator **sim_create_n_operators(int n) {
    if (n < 0) {
        printf(OPERATOR_NUMBER_IS_NEGATIVE_MESSAGE);
        exit(OPERATOR_NUMBER_IS_NEGATIVE);
    }

    Operator **ol = malloc(sizeof(Operator*)*n);
    for (int i=0; i < n; i++) {
        ol[i] = sim_create_operator(-1);
    }
    return ol;
}

void sim_operator_take_client(Operator *o, Call *c) {
    if (o->occupied > 0) {
        printf(OPERATOR_ALREADY_OCCUPIED_MESSAGE);
        exit(OPERATOR_ALREADY_OCCUPIED);
    }
    o->occupied = 1;
    o->ends_in = c->call_duration;
}

int sim_update_operators(Operator** ol, Queue* call_queue, int number_of_operators) {
    for (int i=0; i < number_of_operators; i++) {
        if (ol[i]->occupied == 0) {
            if (queue_is_empty(call_queue)) continue;
            sim_operator_take_client(ol[i], (Call*)queue_dequeue(call_queue));
            continue;
        }

        if ((ol[i]->occupied == 1) && (ol[i]->ends_in == 0)) {
            ol[i]->occupied = 0;
            ol[i]->ends_in = -1;
            continue;
        }

        ol[i]->ends_in--;
    }
}

void sim_log_call(SimResults *results, Call *call) {
    if (results->calls_current_size == results->calls_max_size) {
        Call **nc = realloc(results->calls, sizeof(Call*)*(results->calls_max_size + 5));
        if (nc == NULL) {
            printf(COULDNT_ALLOCATE_MEMORY_MESSAGE);
            exit(COULDNT_ALLOCATE_MEMORY);
        }
        results->calls = nc;
        results->calls_max_size += 5;
    }
    results->calls[results->calls_current_size] = call;
    results->calls_current_size++;
}

SimResults *sim_start_simulation(Arguments *a) {
    SimResults *results = malloc(sizeof(SimResults));
    results->calls_max_size = 1;
    results->calls_current_size = 0;
    results->calls = malloc(sizeof(Call*)*results->calls_max_size);

    results->has_stats = 1; //TODO: add argument to control this
    if (results->has_stats) results->stats = stats_create_stats(a->number_of_days);

    // Any time_t coming from Arguments is guaranteed to be in seconds
    time_t day_duration = a->shift_closing - a->shift_opening;

    Queue *call_queue = queue_init(SIZE_OF_CALL_QUEUE);
    Operator **operators = sim_create_n_operators(a->operators);

    int next_call_id = 0;
    time_t next_call =  misc_int_to_seconds((int) misc_gen_exponential(a->lambda, 1));
    // Here the times can be added because they're guaranteed to be in seconds.
    time_t next_call_duration = (time_t) (a->max_call_duration - a->min_call_duration) * 
        misc_gen_uniform(
            a->min_call_duration,
            a->max_call_duration,
            0
        );

    for (int day = 1; day <= a->number_of_days; day++) {
        int day_tick = 0;
        while ((day_tick < day_duration) || !queue_is_empty(call_queue)) {
            
            //TODO: update stats if needed

            sim_update_operators(operators, call_queue, a->operators);

            // Receiving next clients 
            if (next_call > day_duration)  {
                day_tick++;
                continue;
            }
            if (day_tick == next_call) {
                Call *call = call_create_random(next_call_id, next_call, next_call_duration);
                if (queue_is_full(call_queue)) {
                    printf(CALL_QUEUE_IS_FULL_MESSAGE);
                    exit(CALL_QUEUE_IS_FULL);
                }
                queue_enqueue(call_queue, call);
                sim_log_call(results, call);
                printf("Call_id: %i\n", next_call_id);

                next_call_id++;
                next_call += 1 + misc_int_to_seconds((int) misc_gen_exponential(a->lambda, 0));
                time_t next_call_duration = (time_t) (a->max_call_duration - a->min_call_duration) * 
                    misc_gen_uniform(
                        a->min_call_duration,
                        a->max_call_duration,
                        0
                    );
            }

            day_tick++;
        }
    }

    return results;
}