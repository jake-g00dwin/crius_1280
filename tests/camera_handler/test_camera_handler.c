#include <stdarg.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <setjmp.h>
#include <cmocka.h>

#include "camera_handler.h"


/*
 * ###################################
 * MOCKS
 * ##################################
 */

/*
 * ###################################
 * END OF MOCKS
 * ##################################
 */


/*
 * ############################
 * Tests for SDK interface. 
 * ############################
 */

static void test_camera_init(void **state) { 
    assert_true(1);
}

static void test_args_camera_init(void **state) {
    assert_true(1);
} 


/* A test case that does nothing and succeeds. */
static void null_test_success(void **state) {
    (void) state; /* unused */
}

int main(void)
{
     
    const struct CMUnitTest tests[] = {
        cmocka_unit_test(null_test_success),
        cmocka_unit_test(test_args_camera_init),
        cmocka_unit_test(test_camera_init),
    };
    return cmocka_run_group_tests(tests, NULL, NULL);
}
