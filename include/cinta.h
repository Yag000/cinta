#ifndef CINTA_H
#define CINTA_H

#include <stdbool.h>

#define CHECK(checker, actual, expected, info) checker(actual, expected, __LINE__, __FILE__, info)
#define CHECK_NULL(actual, info) check_null(actual, __LINE__, __FILE__, info)

typedef enum speed_level { SLOW, FAST } speed_level;

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

typedef struct test_case {
    const speed_level speed;
    const char *name;
    void (*function)(test_info *);
} test_case;

test_info *run_cases(const char *name, test_case *functions, int num_functions);

// A test is a function that takes no arguments and returns a test_info*
typedef test_info *(*test)();

int run_tests(test *tests, int num_tests);

void check_string(const char *, const char *, int, const char *, test_info *);
void check_boolean(bool, bool, int, const char *, test_info *);
void check_int(int, int, int, const char *, test_info *);
void check_null(void *actual, int line, const char *file, test_info *info);

#endif // CINTA_H