#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#include "../include/cinta.h"

static void print_green() {
    printf("\033[0;32m");
}

static void print_red() {
    printf("\033[0;31m");
}

static void print_no_color() {
    printf("\033[0m");
}

/** Creates a new test_info. */
test_info *create_test_info() {
    test_info *info = malloc(sizeof(test_info));
    assert(info != NULL);
    info->passed = 0;
    info->failed = 0;
    info->total = 0;
    info->time = 0;

    return info;
}

/** Destroys the test_info . */
void destroy_test_info(test_info *info) {
    free(info);
}

/** Prints the test info. */
void print_test_info(const test_info *info) {
    if (info->failed > 0) {
        print_red();
    } else {
        print_green();
    }
    printf("passed: %d, failed: %d, total: %d, time: %f seconds\n", info->passed, info->failed, info->total,
           info->time);
    print_no_color();
}

double clock_ticks_to_seconds(clock_t ticks) {
    return (double)ticks / CLOCKS_PER_SEC;
}

void print_test_header(const char *name) {
    if (debug) {
        printf("\n----------------------- Testing %s -----------------------\n", name);
    }
}

void print_test_footer(const char *name, const test_info *info) {
    if (debug) {
        printf("\n");
    }

    printf("Test %s: ", name);
    print_test_info(info);

    if (debug) {
        printf("\n----------------------- End test %s -----------------------\n", name);
    }
}

void print_test_name(const char *name) {
    if (debug) {
        printf("\n-> %s\n", name);
    }
}

void run_case(test_case test, test_info *info) {
    print_test_name(test.name);
    test.function(info);
}

test_info *run_cases(const char *name, test_case *cases, int size) {
    print_test_header(name);
    clock_t start = clock();
    test_info *info = create_test_info();

    for (int i = 0; i < size; i++) {
        run_case(cases[i], info);
    }

    info->time = clock_ticks_to_seconds(clock() - start);
    print_test_footer(name, info);
    return info;
}

static void update_test_info(test_info *target_info, test_info *origin_info) {
    target_info->passed += origin_info->passed;
    target_info->failed += origin_info->failed;
    target_info->total += origin_info->total;

    destroy_test_info(origin_info);
}

int run_tests(test *tests, int size) {
    // Create the test info
    test_info *info = create_test_info();
    clock_t start = clock();

    for (int i = 0; i < size; i++) {
        test_info *test_info = tests[i]();
        update_test_info(info, test_info);
    }

    // End of tests
    clock_t end = clock();
    info->time = clock_ticks_to_seconds(end - start);
    bool success = info->passed == info->total;

    printf("\nTotal: ");
    print_test_info(info);
    destroy_test_info(info);

    return success ? EXIT_SUCCESS : EXIT_FAILURE;
}

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
