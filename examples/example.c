#include <unistd.h>

#include "../include/cinta.h"
#include "tests.h"

test tests[2] = {test_test, test_test2};

int main(int argc, char *argv[]) {
    return cinta_main(argc, argv, tests, 2);
}
