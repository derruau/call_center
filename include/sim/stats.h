#ifndef SIM_STATS
#define SIM_STATS

#include "sim/types.h"

Stats *stats_create_stats(int number_of_days);

UncomputedAverage *update_ua(UncomputedAverage *ua, int value);

void stats_update_queue_stats(Stats *s, Queue *call_queue, UncomputedAverage *avg);

void stats_compute_stats(Stats *s, Call **calls, UncomputedAverage *avg_call_queue_size, int number_of_calls, int total_number_of_ticks);

void stats_compute_real_closing_time(Stats *s, int day_number, int day_tick);
#endif