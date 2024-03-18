#include <unistd.h>

#include "../include/cinta.h"
#include "tests.h"

bool debug = false;
bool allow_slow = true;

test tests[] = {test_test, test_test2};

CINTA_MAIN(tests)
