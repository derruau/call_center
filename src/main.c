#include "../include/call.h"
#include <stdlib.h>
#include <stdio.h>

int main() {
    Call *c = create_random_call(0);

    print_call(c);

    free_call(c);
}