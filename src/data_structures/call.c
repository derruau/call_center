#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <stdbool.h>

#define ZERO_ASCII 48
#define MAX_WAIT_TIME_SECONDS 300
#define MAX_CALL_TIME_SECONDS 6000 
#define MAX_CALL_INTERVAL_SECONDS 60
#define NAMES_PATH "data/mock_client_names.csv"

// Forward declarations
float helper_gen_poisson(float lambda, bool seed);
float helper_gen_uniform(float min, float max, bool seed);
time_t helper_add_seconds(time_t t1, int t2);
char* helper_get_random_name_from_file(char *path);

typedef struct call {
    int id;
    char *tel;
    char *client_name;
    time_t call_start;
    time_t wait_time;
    time_t call_end;
} Call;

//TODO: Add client name
Call *call_create_random(int id, time_t call_start, time_t call_end) {
    Call *c = malloc(sizeof(Call));

    c->tel = malloc(sizeof(char)*11);
    c->tel[0] = '0';
    c->tel[1] = '6';
    for (int i=2; i<10; i++) {
        char n = ZERO_ASCII + (rand() % 10);
        c->tel[i] = n;
    }
    c->tel[10] = '\0';

    c->id = id;
    c->client_name = helper_get_random_name_from_file(NAMES_PATH);
    c->wait_time = -1; // Calculated at runtime
    c->call_start = call_start;
    c->call_end = call_end;

    return c;
}

void call_free(Call *c) {
    free(c->tel);
    free(c->client_name);
    free(c);
}

Call **call_create_n_random(
    int n,
    time_t shift_start, 
    time_t shift_end, 
    float lamba,
    float minsrv,
    float maxsrv
    ) {
    Call **calls = malloc(sizeof(Call*)*n);

    time_t prev_call = shift_start;
    for (int i=0; i< n; i++) {
        int call_start_delta = (int)MAX_CALL_INTERVAL_SECONDS*helper_gen_poisson(lamba, i==0);
        int call_end_delta = (int)MAX_CALL_TIME_SECONDS*helper_gen_uniform(minsrv, maxsrv, false);

        time_t call_start = helper_add_seconds(prev_call, call_start_delta);
        printf("%s\n", ctime(&call_start)); 
        time_t call_end = helper_add_seconds(call_start, call_end_delta);
	printf("%s  ", ctime(&call_start)); 
	printf("\n");
        calls[i] = call_create_random(i, call_start, call_end);

        prev_call = call_start;

    }
    return calls;
}
