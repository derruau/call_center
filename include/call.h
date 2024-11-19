#ifndef HEADER_FILE_NAME
#define HEADER_FILE_NAME

typedef struct {
    int id;
    char *tel;
} Call;

Call *create_random_call(int id);

void free_call(Call *c);

void print_call(Call *c);

#endif