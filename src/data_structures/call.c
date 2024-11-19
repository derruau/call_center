#include <stdlib.h>
#include <stdio.h>

#define ZERO_ASCII 48

typedef struct {
    int id;
    char *tel;
} Call;

Call *call_create_random(int id) {
    Call *c = malloc(sizeof(Call));

    char *tel = malloc(sizeof(char)*10);
    tel[0] = '0';
    tel[1] = '6';
    for (int i=2; i<10; i++) {
        char n = ZERO_ASCII + (rand() % 10);
        tel[i] = n;
    }

    c->id = id;
    c->tel = tel;

    return c;
}

void call_free(Call *c) {
    free(c->tel);
    free(c);
}