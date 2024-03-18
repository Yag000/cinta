#include <string.h>
#include <unistd.h>

#include "test_core.h"

bool debug;
bool allow_slow = true;

/** This is the main function for the test program. Every test should be
 * called from here and the results will be printed.
 */
int main(int argc, char *argv[]) {
    if (argc > 1) {
        for (int i = 1; i < argc; i++) {
            if (strcmp(argv[i], "-v") == 0) {
                debug = true;
            }
            if (strcmp(argv[i], "-q") == 0) {
                allow_slow = false;
            }
        }
    }

    test tests[] = {test_test, test_test2};

    return run_tests(tests, 2);
}
