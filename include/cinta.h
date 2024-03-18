#ifndef CINTA_H
#define CINTA_H

#include <stdbool.h>
#include <string.h>

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

typedef enum speed_level { SLOW, QUICK } speed_level;

typedef struct test_case {
    const speed_level speed;
    const char *name;
    void (*function)(test_info *);
} test_case;

#define TEST_CASE(name, speed, function)                                                                               \
    { speed, name, function }

#define SLOW_CASE(name, function) TEST_CASE(name, SLOW, function)
#define QUICK_CASE(name, function) TEST_CASE(name, QUICK, function)

test_info *run_cases(const char *name, test_case *functions, int num_functions);

// A test is a function that takes no arguments and returns a test_info*
typedef test_info *(*test)();

int run_tests(test *tests, int num_tests);

void check_string(const char *, const char *, int, const char *, test_info *);
void check_boolean(bool, bool, int, const char *, test_info *);
void check_int(int, int, int, const char *, test_info *);
void check_null(void *actual, int line, const char *file, test_info *info);

#define CINTA_MAIN(tests)                                                                                              \
    int main(int argc, char *argv[]) {                                                                                 \
        if (argc > 1) {                                                                                                \
            for (int i = 1; i < argc; i++) {                                                                           \
                if (strcmp(argv[i], "-v") == 0) {                                                                      \
                    debug = true;                                                                                      \
                }                                                                                                      \
                if (strcmp(argv[i], "-q") == 0) {                                                                      \
                    allow_slow = false;                                                                                \
                }                                                                                                      \
            }                                                                                                          \
        }                                                                                                              \
        return run_tests(tests, sizeof(tests) / sizeof(tests[0]));                                                     \
    }
#endif // CINTA_H
