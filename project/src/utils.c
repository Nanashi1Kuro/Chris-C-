#include "utils.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

size_t timer_from(int from) {
    size_t counter = 0;
    for (int i = from; i > 0; --i) {
        ++counter;
        printf("%i ",i);
    }
    printf("0");
    printf("\n");
    return ++counter;
}

// TODO: Implement `power of` function
/*
int custom_pow(int base, int power) {
    return 0;
}
*/
