#ifndef HEADER_CALL
#define HEADER_CALL

typedef struct {
    int id;
    char *tel;
} Call;

Call *call_create_random(int id);

void call_free(Call *c);

#endif