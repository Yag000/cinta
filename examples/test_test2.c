#include "tests.h"
#include <stdlib.h>

#define NUMBER_TESTS 2

void test_testo2(test_info *info) {
    CINTA_ASSERT_INT(1, 0, info);
}

void test_null2(test_info *info) {
    CINTA_ASSERT_NULL(NULL, info);
}

test_info *test_test2() {
    test_case cases[NUMBER_TESTS] = {QUICK_CASE("testo2", test_testo2), QUICK_CASE("null2", test_null2)};
    return cinta_run_cases("test2", cases, NUMBER_TESTS);
}
