#include <stdarg.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <setjmp.h>
#include <cmocka.h>

#include "camera_handler.h"
#include "camera_test_wrap.h"


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
    HANDLE my_handle = NULL;
    assert_null(my_handle);

    //my_handle = init_camera(30, true, 1, eAGCLocal, 1);
    assert_non_null(my_handle);

}

static void test_args_camera_init(void **state) {
    assert_true(1);
}

static void test_num_attached(void **state) {
    //Proxy1280_12USB_GetModuleName
    int num = num_attached();
    assert_true(num > 0);
}


/* A test case that does nothing and succeeds. */
static void null_test_success(void **state) {
    (void) state; /* unused */
}

int main(void)
{

    const struct CMUnitTest init_tests[] = {
        cmocka_unit_test(test_camera_init),
        cmocka_unit_test(test_args_camera_init),
    };

    const struct CMUnitTest tests[] = {
        cmocka_unit_test(test_num_attached),
        cmocka_unit_test(null_test_success),
    };
    cmocka_run_group_tests(init_tests, NULL,NULL);
    return cmocka_run_group_tests(tests, NULL, NULL);
}
