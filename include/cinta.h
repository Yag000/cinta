/* Cinta - Small C testing framework
 * Source code available at: https://github.com/Yag000/cinta
 * Author: Yago Iglesias Vázquez <yago.iglesias.vazquez@gmail.com>
 * License: MIT
 */

#ifndef CINTA_H
#define CINTA_H

#include <stdbool.h>
#include <stdio.h>
#include <string.h>

void cinta_log(const char *fmt, ...);

#define CINTA_LOG_BOOL(bool, info, fmt, ...)                                                                           \
    info->total++;                                                                                                     \
    if (bool) {                                                                                                        \
        info->passed++;                                                                                                \
    } else {                                                                                                           \
        cinta_log(fmt, ##__VA_ARGS__);                                                                                 \
        info->failed++;                                                                                                \
    }

#define CINTA_ASSERT_PRIMITIVE(T, actual, op, expected, fmt, file, line, info)                                         \
    do {                                                                                                               \
        T actual_val = (actual);                                                                                       \
        T expected_val = (expected);                                                                                   \
        CINTA_LOG_BOOL(actual_val op expected_val, info, "Failed: %s:%d: expected " fmt ", got " fmt "\n", file, line, \
                       expected_val, actual_val);                                                                      \
    } while (0)

#define CINTA_ASSERT(boolean, info) CINTA_LOG_BOOL(boolean, info, "Failed: %s:%d\n", __FILE__, __LINE__)

#define CINTA_ASSERT_FALSE(boolean, info) CINTA_ASSERT(!(boolean), info)

#define CINTA_ASSERT_INT(actual, expected, info)                                                                       \
    CINTA_ASSERT_PRIMITIVE(int, actual, ==, expected, "%d", __FILE__, __LINE__, info)

#define CINTA_ASSERT_CHAR(actual, expected, info)                                                                      \
    CINTA_ASSERT_PRIMITIVE(char, actual, ==, expected, "%c", __FILE__, __LINE__, info)

#define CINTA_ASSERT_PTR(actual, op, expected, info)                                                                   \
    CINTA_ASSERT_PRIMITIVE(const void *, actual, op, expected, "%p", __FILE__, __LINE__, info)

#define CINTA_ASSERT_NULL(actual, info) CINTA_ASSERT_PTR(actual, ==, NULL, info)

#define CINTA_ASSERT_NOT_NULL(actual, info) CINTA_ASSERT_PTR(actual, !=, NULL, info)

#define CINTA_CUSTOM_ASSERT(actual, expected, check, info)                                                             \
    CINTA_LOG_BOOL(check(actual, expected), info, "Failed: %s:%d\n", __FILE__, __LINE__)

#define CINTA_ASSERT_STRING(actual, expected, info)                                                                    \
    CINTA_LOG_BOOL(strcmp(actual, expected) == 0, info, "Failed: %s:%d: expected \"%s\", got \"%s\"\n", __FILE__,      \
                   __LINE__, expected, actual)

/** Structure to hold test information. */
typedef struct test_info {
    int passed;
    int failed;
    int total;
    double time;
} test_info;

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

test_info *cinta_run_cases(const char *name, test_case *functions, int num_functions);

// A test is a function that takes no arguments and returns a test_info*
typedef test_info *(*test)();

int cinta_main(int argc, char *argv[], test *tests, size_t num_tests);

#endif // CINTA_H
