#include <unistd.h>

#include "../include/cinta.h"
#include "tests.h"

#define NUMBER_TESTS 2

test tests[NUMBER_TESTS] = {test_test, test_test2};

int main(int argc, char *argv[]) {
    return cinta_main(argc, argv, tests, NUMBER_TESTS);
}
