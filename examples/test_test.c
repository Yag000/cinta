#include <stdio.h>
#include <stdlib.h>

#include "tests.h"

void test_testo(test_info *info);
void test_null(test_info *info);

test_info *test_test() {
    test_case cases[2] = {SLOW_CASE("testo", test_testo), SLOW_CASE("null", test_null)};
    return run_cases("test", cases, 2);
}

void test_testo(test_info *info) {
    CINTA_CHECK(1, info);
}

void test_null(test_info *info) {
    CINTA_CHECK_NULL(NULL, info);
}
