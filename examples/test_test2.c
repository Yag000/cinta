#include "tests.h"
#include <stdlib.h>

void test_testo2(test_info *info) {
    CINTA_CHECK_INT(1, 0, info);
}

void test_null2(test_info *info) {
    CINTA_CHECK_NULL(NULL, info);
}

test_info *test_test2() {
    test_case cases[2] = {QUICK_CASE("testo2", test_testo2), QUICK_CASE("null2", test_null2)};
    return run_cases("test2", cases, 2);
}
