#include "utils.h"
#include <stdio.h>
#include <time.h>

void print_green() {
    printf("\033[0;32m");
}

void print_red() {
    printf("\033[0;31m");
}

void print_no_color() {
    printf("\033[0m");
}


double clock_ticks_to_seconds(clock_t ticks) {
    return (double)ticks / CLOCKS_PER_SEC;
}

