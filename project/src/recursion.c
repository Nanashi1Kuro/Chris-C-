#include "utils.h"
#include <stdio.h>

void recursion(int n) {
    if (n > 0) {
        if (n == 1) {
            printf("%i", n);} else {
            recursion(n-1);
            printf(" %i", n);}} else {
        recursion(n+1);
        printf(" %i", n);}
}
