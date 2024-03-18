#include "tests.h"
#include <stdlib.h>

void test_testo2(test_info *info) {
    CHECK(check_boolean, 1, 1, info);
}

void test_null2(test_info *info) {
    CHECK_NULL(NULL, info);
}

test_info *test_test2() {
    test_case cases[2] = {{"testo2", test_testo2}, {"null2", test_null2}};
    return run_cases("test2", cases, 2);
}
