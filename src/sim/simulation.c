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

#define MAX_CALL_INTERVAL_SECONDS 60

Stats *sim_create_stats(int number_of_days) {
    Stats *s = malloc(sizeof(Stats));

    s->min_queue_size = 0;
    s->max_queue_size = 0;
    s->avg_queue_size = 0;

    s->min_call_wait_time = 0;
    s->max_call_wait_time = 0;
    s->avg_call_wait_time = 0;

    s->avg_daily_call_rate = 0;

    s->handled_customer_rate = malloc(sizeof(float)*number_of_days);
    s->non_handled_customer_rate = malloc(sizeof(float)*number_of_days);

    s->avg_response_time = 0;

    s->daily_real_closing_time = malloc(sizeof(time_t)*number_of_days);

    return s;
}

SimResults *sim_start_simulation(Arguments *a) {
    SimResults *results = malloc(sizeof(SimResults));
    results->has_stats = 1; //TODO: add argument to control this
    if (results->has_stats) results->stats = sim_create_stats(a->number_of_days);

    // Any time_t coming from Arguments is guaranteed to be in seconds
    time_t day_duration = a->maxsrv - a->minsrv;

    int next_call = MAX_CALL_INTERVAL_SECONDS*misc_gen_poisson(a->lambda, 0);

    printf("%li", misc_to_seconds(5));

    // for (int day = 1; day <= a->number_of_days; day++) {
    //     for (int day_tick=0; day_tick < day_duration; day_tick++) {
            
    //     }
    // }
}