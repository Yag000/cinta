#include <stdio.h>
#include <stdlib.h>

#include "test_core.h"

void test_testo(test_info *info);
void test_null(test_info *info);

test_info *test_test() {
    test_case cases[2] = {{"testo", test_testo}, {"null", test_null}};
    return run_cases("test", cases, 2);
}

void test_testo(test_info *info) {
    CHECK(check_boolean, 1, 0, info);
}

void test_null(test_info *info) {
    CHECK_NULL(NULL, info);
}
