#ifndef TEST_CORE_H
#define TEST_CORE_H

#include <limits.h>
#include <stdbool.h>
#include <time.h>

#define CHECK(checker, actual, expected, info) checker(actual, expected, __LINE__, __FILE__, info)
#define CHECK_NULL(actual, info) check_null(actual, __LINE__, __FILE__, info)

extern bool debug;
extern bool allow_slow;

/** Structure to hold test information. */
typedef struct test_info {
    int passed;
    int failed;
    int total;
    double time;
} test_info;

test_info *create_test_info();
void destroy_test_info(test_info *);
void print_test_info(const test_info *);

// Test utils
double clock_ticks_to_seconds(clock_t);

typedef void (*TestFunction)(test_info *);

test_info *run_cases(const char *config, TestFunction *functions, int num_functions);

void check_string(const char *, const char *, int, const char *, test_info *);
void check_boolean(bool, bool, int, const char *, test_info *);
void check_int(int, int, int, const char *, test_info *);
void check_null(void *actual, int line, const char *file, test_info *info);

// All the tests
test_info *test_test();

#endif // TEST_CORE_H
