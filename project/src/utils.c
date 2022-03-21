#include "utils.h"

size_t countdown_from(int number) {
    size_t counter = 0;
    if (number < 0) {
        return counter;
    }
    for (int i = number; i > 0; --i) {
        ++counter;
        printf("%i ", i);
    }
    printf("0");
    printf("\n");
    return ++counter;
}
