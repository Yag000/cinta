/* Cinta - Small C testing framework
 * Source code available at: https://github.com/Yag000/cinta
 * Author: Yago Iglesias Vázquez <yago.iglesias.vazquez@gmail.com>
 * License: MIT
 */

#include <assert.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#include "cinta.h"

static bool debug = false;
static bool allow_slow = true;

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

void cinta_log(const char *fmt, ...) {
    print_red();

    va_list args;
    va_start(args, fmt);
    vprintf(fmt, args);
    va_end(args);

    print_no_color();
}

void run_case(test_case test, test_info *info) {
    if (!allow_slow && test.speed == SLOW) {
        return;
    }

    print_test_name(test.name);
    test.function(info);
}

test_info *cinta_run_cases(const char *name, test_case *cases, int size) {
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

int cinta_main(int argc, char *argv[], test *tests, size_t size) {
    if (argc > 1) {
        for (int i = 1; i < argc; i++) {
            if (strcmp(argv[i], "-v") == 0) {
                debug = true;
            }
            if (strcmp(argv[i], "-q") == 0) {
                allow_slow = false;
            }
        }
    }
    return run_tests(tests, size);
}
