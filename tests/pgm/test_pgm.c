#include <fcntl.h>
#include <stdarg.h>
#include <stddef.h>
#include <stdint.h>
#include <setjmp.h>
#include <cmocka.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

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


/*
 * ############################
 * Tests for PGM
 * ############################
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


static void test_pgm_new(void **state) {
    pgm_t test_image = new_pgm_image(1920, 1080);
    assert_true(test_image.width == 1920);
    assert_true(test_image.height == 1080);
}


static void test_save_pgm_image(void **state) {
    char s[] = "/tmp/test_image.pgm";

    pgm_t test_image = new_pgm_image(600, 600);
    
    char* file_contents = malloc(600);


    int result = save_pgm_image(&test_image, s);
    
    assert_true(result == 0);

    //now check if the image file exists by opening it.
    int fd = open(s, O_RDONLY);

    //Check if it 1.) Exists, 2.) Opens without issue.
    if(fd < 0) {
        assert_true(0);
    }
    
    //check for correct header types
    read(fd, file_contents, 600);
    
    //The first two chars should be 'P5'
    assert_true(file_contents[0] == 'P');
    assert_true(file_contents[1] == '5');
    printf("file_contents: %s\n", file_contents);

    //The next two should be the size parameters
    assert_true(file_contents[4] == '6');
    assert_true(file_contents[5] == '0');
    assert_true(file_contents[6] == '0');
    assert_true(file_contents[7] == ' ');
    assert_true(file_contents[8] == '6');
    assert_true(file_contents[9] == '0');
    assert_true(file_contents[10] == '0');


    int close_result = close(fd);
    assert_true(0 <= close_result);

    free(file_contents);
}

/*
 * ############################
 * Tests for Matrix
 * ############################
 */ 

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
        cmocka_unit_test(test_pgm_new),
        cmocka_unit_test(test_save_pgm_image),
        cmocka_unit_test(test_2dmatrix_struct),
        cmocka_unit_test(test_clear_matrix),

    }; 
    return cmocka_run_group_tests(tests, NULL, NULL);
}
