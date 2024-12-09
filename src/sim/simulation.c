/* 
========================================== SIMULATION.C ==========================================
This file's role is to perform the simulation.

The simulation works like this:
    1. We simulate every second of every day of the simulation.

    2. For each second, we first look to see if the call center is open. Open means either: The 
    second is within it's opening hours and we accept new calls or the second is not within it's 
    opening hours and we are only processing the calls that are already in the queue.
        2.1 We update the operators's state
        2.1 If the call center is open and taking calls, we check if a call has arrived. If it has,
            we queue it.
    
    3. If the call center is closed. We are just checking if any call arrives and reject it.

    4. Once the simulation is over, we calculate it's stats and put them in a SimResult object.

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

#define TICKS_PER_DAY 60*60*24 // Number of seconds in a day

#define OPERATOR_NUMBER_IS_NEGATIVE 501
#define OPERATOR_ALREADY_OCCUPIED 502
#define COULDNT_ALLOCATE_MEMORY 503
#define CALL_QUEUE_IS_FULL 504
#define OPERATOR_NUMBER_IS_NEGATIVE_MESSAGE "[SIMULATION ERROR] - Operator number must be positive!\n"
#define OPERATOR_ALREADY_OCCUPIED_MESSAGE "[SIMULATION ERROR] - Operator is already occupied!\n"
#define COULDNT_ALLOCATE_MEMORY_MESSAGE "[SIMULATION ERROR] - Couldn't allocate more memory to program!\n"
#define CALL_QUEUE_IS_FULL_MESSAGE "[SIMULATION ERROR] - Call Queue of size %i is full! Try adding the '--queue-size %i' option.\n"

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


void sim_operator_take_client(Operator *o, Call *c, int day_tick) {
    if (o->occupied > 0) {
        printf(OPERATOR_ALREADY_OCCUPIED_MESSAGE);
        exit(OPERATOR_ALREADY_OCCUPIED);
    }
    o->occupied = 1;
    o->ends_in = c->call_duration;

    // Compute the call's missing infos
    c->wait_time = (time_t)day_tick - c->call_start;
    if (c->wait_time < 0) c->wait_time = 0; // Sometimes is -1, dirty fix but don't have the time for more
    c->call_end = c->call_start + c->wait_time + c->call_duration;
}


int sim_update_operators(
    Stats *s, 
    UncomputedAverage *ua, 
    Operator** ol, 
    Queue* call_queue, 
    int number_of_operators, 
    int day_tick
    ) {
    
    stats_update_queue_stats(s, call_queue, ua);

    for (int i=0; i < number_of_operators; i++) {
        if (ol[i]->occupied == 0) {
            if (queue_is_empty(call_queue)) continue;
            sim_operator_take_client(ol[i], (Call*)queue_dequeue(call_queue), day_tick);
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


int sim_time_in_open_hours(int time, Arguments *a) {
    return (time >= a->shift_opening) && (time <= a->shift_closing);
}


SimResults *sim_start_simulation(Arguments *a) {
    SimResults *results = malloc(sizeof(SimResults));
    results->calls_max_size = 1;
    results->calls_current_size = 0;
    results->calls = malloc(sizeof(Call*)*results->calls_max_size);

    Stats *s = stats_create_stats(a->number_of_days);
    results->stats = s;

    // To compute the average call queue size in stats
    UncomputedAverage *ua_call_queue_size = malloc(sizeof(UncomputedAverage));
    ua_call_queue_size->count = 0;
    ua_call_queue_size->sum = 0;

    results->has_stats = 1; // Scraped!
    if (results->has_stats) results->stats = stats_create_stats(a->number_of_days);

    Queue *call_queue = queue_init(a->queue_size);
    Operator **operators = sim_create_n_operators(a->operators);

    int next_call_id = 1;
    // time_t next_call =  misc_int_to_seconds((int) misc_gen_exponential(a->lambda, 1));
    // // Here the times can be added because they're guaranteed to be in seconds.
    // time_t next_call_duration = (time_t) misc_gen_uniform(a->min_call_duration, a->max_call_duration, 0);

    // TODO: refactor to make it easier to read.
    // Note: We don't have the time to do this.
    for (int day = 1; day <= a->number_of_days; day++) {
        int day_tick = 0;
        time_t next_call =  misc_int_to_seconds((int) misc_gen_exponential(a->lambda, 1));
        // Here the times can be added because they're guaranteed to be in seconds.
        time_t next_call_duration = (time_t) misc_gen_uniform(a->min_call_duration, a->max_call_duration, 0);
        for (int day_tick =0; day_tick < TICKS_PER_DAY; day_tick++) {

            // If the call center is open
            if (sim_time_in_open_hours(day_tick, a) || !queue_is_empty(call_queue)) {

                sim_update_operators(results->stats, ua_call_queue_size, operators, call_queue, a->operators, day_tick);
                // Next call is in closing hours 
                if (!sim_time_in_open_hours(next_call, a))  {
                    next_call_id++;
                    next_call += 1 + misc_int_to_seconds((int) misc_gen_exponential(a->lambda, 0));
                    time_t next_call_duration = (time_t) misc_gen_uniform(a->min_call_duration, a->max_call_duration, 0);
                    continue;
                }

                if (day_tick == next_call) {
                    Call *call = call_create_random(next_call_id, next_call, next_call_duration, day,a->include_names, a->names_path);
                    if (queue_is_full(call_queue)) {
                        printf(CALL_QUEUE_IS_FULL_MESSAGE, a->queue_size, a->queue_size*2);
                        exit(CALL_QUEUE_IS_FULL);
                    }
                    queue_enqueue(call_queue, call);
                    sim_log_call(results, call); // We only need to log accepted clients

                    next_call_id++;
                    next_call += 1 + misc_int_to_seconds((int) misc_gen_exponential(a->lambda, 0));
                    time_t next_call_duration = (time_t) misc_gen_uniform(a->min_call_duration, a->max_call_duration, 0);
                }
                continue;
            }

            // Here the call center is closed

            // There is a call incoming --> it is rejected
            if (day_tick == next_call) {
                    next_call_id++;
                    next_call += 1 + misc_int_to_seconds((int) misc_gen_exponential(a->lambda, 0));
                    time_t next_call_duration = (time_t) misc_gen_uniform(a->min_call_duration, a->max_call_duration, 0);
            }
        }
        
        stats_compute_real_closing_time(results->stats, day, day_tick);

    }

    stats_compute_stats(results->stats, results->calls, ua_call_queue_size, results->calls_current_size, a->number_of_days*TICKS_PER_DAY);

    return results;
}