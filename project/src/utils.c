#include "utils.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>



size_t timer_from(int from) {
    size_t counter = 0;
    if(from > 0){
        for (int i = from; i > 0; --i) {
            ++counter;
            printf("%i ",i);
        }
        printf("0");
        printf("\n");
        return ++counter;
    }
    else
    return counter;
}

int custom_pow(int base, int power) {
    int res = 1;
    for(int i = 1; i <= power; ++i){
        res *= base;
    }
    return res;
}
