#include "utils.h"

size_t timer_from(int from) {
    size_t counter = 0;
    if (from > 0) {
        for (int i = from; i > 0; --i) {
            ++counter;
            printf("%i ", i);
        }
        printf("0");
        printf("\n");
        return ++counter;
    } else {
        return counter;
    }
}
