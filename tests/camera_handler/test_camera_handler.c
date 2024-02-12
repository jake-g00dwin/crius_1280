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
    int fps = 5;
    bool SL = false;
    bool BP = false;
    enum agc AGC = no_agc; 
    int result = init_camera(fps, SL, BP, AGC);
    assert_true(result == 0);

    fps = 0;
    result = init_camera(fps, SL, BP, AGC);
    assert_false(result == 0);

    fps = 175;
    result = init_camera(fps, SL, BP, AGC);
    assert_false(result == 0);

   
} 


/* A test case that does nothing and succeeds. */
static void null_test_success(void **state) {
    (void) state; /* unused */
}

int main(void)
{
     
    const struct CMUnitTest tests[] = {
        cmocka_unit_test(null_test_success),
        cmocka_unit_test(test_camera_init),
    };
    return cmocka_run_group_tests(tests, NULL, NULL);
}
