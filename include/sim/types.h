#ifndef SIM_TYPES
#define SIM_TYPES

#include <time.h>

//================ call.c types ================
typedef struct call {
    int id;
    char *tel;
    char *client_name;
    int day; // The day of the simulation
    time_t call_start;
    time_t wait_time;
    time_t call_end;
    time_t call_duration;
} Call;

//================ queue.c types ================

typedef struct {
    int front;
    int back;
    int size;
    int number_of_elements;
    void *q[];
} Queue;

//================ stats.c types ================

typedef struct {
    // 1st requirement
    // Minimum, Maximum and Average size of the Call Queue
    int min_queue_size;
    int max_queue_size;
    int avg_queue_size;

    // 2nd requirement
    // Minimum, Maximum and Average wait time for Call
    time_t min_call_wait_time;
    time_t max_call_wait_time;
    time_t avg_call_wait_time;

    // 3rd requirement
    // Average number of handled calls per unit of time 
    float avg_daily_call_rate;

    //4th requirement
    // Daily rate of handled
    float handled_customer_rate;

    //5th requirement
    // Average response tim
    time_t avg_response_time;

    //6th requirement
    // The time at which the last operator finished his
    // last call for the day.
    // It's a list I think??
    time_t* daily_real_closing_time;
} Stats;

typedef struct {
    int sum;
    int count;
} UncomputedAverage;

//================ simulation.c types ================


typedef struct {
    int has_stats;
    Stats *stats;
    
    Call **calls;
    int calls_current_size;
    int calls_max_size;
} SimResults;

typedef struct {
    int occupied;
    time_t ends_in;
} Operator;

#endif