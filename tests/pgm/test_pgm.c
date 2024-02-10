#include <stdarg.h>
#include <stddef.h>
#include <stdint.h>
#include <setjmp.h>
#include <cmocka.h>

#include "pgm.h" 
//GLOBALS???


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


/*Test case for ensuring the correct structures exist.*/
static void test_pgm_struct(void **state) {
    (void) state;

    pgm_t my_pgm_img;
    my_pgm_img.val = 1;
    assert_true(my_pgm_img.val);
}


/* A test case that does nothing and succeeds. */
static void null_test_success(void **state) {
    (void) state; /* unused */
}

int main(void)
{
    const struct CMUnitTest tests[] = {
        cmocka_unit_test(null_test_success),
        cmocka_unit_test(test_pgm_struct),
    }; 
    return cmocka_run_group_tests(tests, NULL, NULL);
}
