#include <stdio.h>
#include <stdlib.h>

#include "tests.h"

#define NUMBER_TESTS 2

void test_testo(test_info *info);
void test_null(test_info *info);

test_info *test_test() {
    test_case cases[NUMBER_TESTS] = {SLOW_CASE("testo", test_testo), SLOW_CASE("null", test_null)};
    return run_cases("test", cases, NUMBER_TESTS);
}

void test_testo(test_info *info) {
    CINTA_ASSERT(1, info);
}

void test_null(test_info *info) {
    CINTA_ASSERT_NULL(NULL, info);
}
