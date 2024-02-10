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
    
    my_pgm_img.width = 1920;
    my_pgm_img.height = 1080;

    my_pgm_img.data_matrix.x = 1920;
    my_pgm_img.data_matrix.y = 1080;


    //Now try to access the 2d data array. 
    assert_non_null(my_pgm_img.data_matrix.x);
}

/*Test case for the 2D matrix implimentation.*/
static void test_2dmatrix_struct(void **state)
{
    matrix_t my_matrix;
    my_matrix.x = 1920;
    my_matrix.y = 1080;

    assert_in_range(my_matrix.x, 0, MAX_2D_COLS);
    assert_in_range(my_matrix.y, 0, MAX_2D_ROWS);

}

static void test_clear_matrix(void **state)
{
    matrix_t my_matrix;

    my_matrix.x = 1920;
    my_matrix.y = 1080;
    
    clear_matrix(&my_matrix);
    
    for(int row = 0; row < MAX_2D_ROWS; row++) {
        for(int col = 0; col < MAX_2D_COLS; col++){
            assert_true(my_matrix.data[col][row] == 0);
        }
    }
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
        cmocka_unit_test(test_2dmatrix_struct),
        cmocka_unit_test(test_clear_matrix),
    }; 
    return cmocka_run_group_tests(tests, NULL, NULL);
}
