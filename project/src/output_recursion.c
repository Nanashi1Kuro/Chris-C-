#include "utils.h"

void output_recursion(int number) {
    if (number > 0) {
        if (number == 1) {
            printf("%i", number);
        }
        if (number != 1) {
            output_recursion(number-1);
            printf(" %i", number);
        }
    }
    if (number <= 0) {
        output_recursion(number+1);
        printf(" %i", number);
    }
}
