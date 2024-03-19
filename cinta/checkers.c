#include <stdio.h>
#include <string.h>

#include "../include/cinta.h"
#include "utils.h"

void check_string(const char *expected, const char *actual, int line, const char *file, test_info *info) {
    info->total++;
    if (strcmp(expected, actual) != 0) {
        print_red();
        printf("Error: '%s' != '%s' at line %d in file %s\n", expected, actual, line, file);
        print_no_color();
        info->failed++;
        return;
    }
    if (debug) {
        print_green();
        printf("Passed: '%s' == '%s' at line %d in file %s\n", expected, actual, line, file);
        print_no_color();
    }
    info->passed++;
}

void check_boolean(bool expected, bool actual, int line, const char *file, test_info *info) {
    info->total++;
    if (expected != actual) {
        print_red();
        printf("Error: %d != %d at line %d in file %s\n", expected, actual, line, file);
        print_no_color();
        info->failed++;
        return;
    }
    if (debug) {
        print_green();
        printf("Passed: %d == %d at line %d in file %s\n", expected, actual, line, file);
        print_no_color();
    }
    info->passed++;
}

void check_int(int expected, int actual, int line, const char *file, test_info *info) {
    info->total++;
    if (expected != actual) {
        print_red();
        printf("Error: %d != %d at line %d in file %s\n", expected, actual, line, file);
        print_no_color();
        info->failed++;
        return;
    }
    if (debug) {
        print_green();
        printf("Passed: %d == %d at line %d in file %s\n", expected, actual, line, file);
        print_no_color();
    }
    info->passed++;
}

void check_null(void *actual, int line, const char *file, test_info *info) {
    info->total++;
    if (NULL != actual) {
        print_red();
        printf("Error: pointer should be NULL at line %d in file %s\n", line, file);
        print_no_color();
        info->failed++;
        return;
    }
    if (debug) {
        print_green();
        printf("Passed: NULL pointer at line %d in file %s\n", line, file);
        print_no_color();
    }
    info->passed++;
}
