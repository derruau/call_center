/* 
========================================== STATS.C ==========================================
This file's role is compute all the stats associated with the simulation

It's main function (stats_update_stats) is called at every tick in the simulation. We need
to take this into account in the code.

This program needs to compte several averages, but 

========================================== STATS.C ==========================================
*/

#include "sim/types.h"
#include <stdlib.h>

Stats *stats_create_stats(int number_of_days) {
    Stats *s = malloc(sizeof(Stats));

    s->min_queue_size = 0;
    s->max_queue_size = 0;
    s->avg_queue_size = 0;

    s->min_call_wait_time = 0;
    s->max_call_wait_time = 0;
    s->avg_call_wait_time = 0;

    s->avg_daily_call_rate = 0;

    s->handled_customer_rate = 0;

    s->avg_response_time = 0;

    s->daily_real_closing_time = malloc(sizeof(time_t)*number_of_days);

    return s;
}

UncomputedAverage *update_ua(UncomputedAverage *ua, int value) {
    ua->sum += value;
    ua->count++;

    return ua;
}

void stats_update_queue_stats(Stats *s, Queue *call_queue, UncomputedAverage *avg) {

    if (call_queue->number_of_elements > s->max_queue_size) s->max_queue_size = call_queue->number_of_elements;
    
    if (call_queue->number_of_elements < s->min_queue_size) s->min_queue_size = call_queue->number_of_elements;

    update_ua(avg, call_queue->number_of_elements);
}

void stats_compute_stats(Stats *s, Call **calls, UncomputedAverage *avg_call_queue_size, int number_of_calls, int total_number_of_ticks) {
    time_t min_call_wait_time = calls[0]->wait_time;
    time_t max_call_wait_time = calls[0]->wait_time;
    time_t avg_call_wait_time = 0;

    int avg_daily_call_rate = 0;

    time_t avg_response_time = 0;

    for (int i=0; i < number_of_calls; i++) {
        if (calls[i]->wait_time > max_call_wait_time) max_call_wait_time = calls[i]->wait_time;

        if (calls[i]->wait_time < min_call_wait_time) min_call_wait_time = calls[i]->wait_time;

        avg_call_wait_time += calls[i]->wait_time;

        avg_response_time += calls[i]->call_duration;

    }

    avg_call_wait_time /= (float)number_of_calls;

    avg_daily_call_rate = number_of_calls / (float)total_number_of_ticks;

    avg_response_time /= (float)number_of_calls;

    // Putting stats into the Stats struct
    
    //min_queue_size & max_queue_size are already set by stats_update_queue_stats()
    s->avg_call_wait_time = avg_call_queue_size->sum / (float)avg_call_queue_size->count;

    s->min_call_wait_time = min_call_wait_time;
    s->max_call_wait_time = max_call_wait_time;
    s->avg_call_wait_time = avg_call_wait_time;

    s->avg_daily_call_rate = avg_daily_call_rate;

    s->handled_customer_rate = calls[number_of_calls - 1]->id / (float)number_of_calls;
    
    s->avg_response_time = avg_response_time;

    // daily_real_closing_time is set by stats_compute_real_closing_time()
}

void stats_compute_real_closing_time(Stats *s, int day_number, int day_tick) {
    s->daily_real_closing_time[day_number - 1] = day_tick;
}