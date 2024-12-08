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

    s->handled_customer_rate = malloc(sizeof(float)*number_of_days);
    s->non_handled_customer_rate = malloc(sizeof(float)*number_of_days);

    s->avg_response_time = 0;

    s->daily_real_closing_time = malloc(sizeof(time_t)*number_of_days);

    return s;
}