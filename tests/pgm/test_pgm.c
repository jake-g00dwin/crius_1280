#include <fcntl.h>
#include <stdarg.h>
#include <stddef.h>
#include <stdint.h>
#include <setjmp.h>
#include <cmocka.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include "pgm.h" 


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

static void test_build_pgm_header(void **state) {

    /*Check for correct sting function*/
    char h[128] = {'\0'};
    int result = sprintf(h, "P5\n%u %u\n%u", 1280, 1024, UINT16_MAX);
    assert_true(result >= 0);

    result = strcmp(h, "P5\n1280 1024\n255");
    assert_true(result >= 0);
   
    char header[128] = {'\0'};
    pgm_t test_image = new_pgm_image(1280, 1024);

    /*Call the function*/
    result = build_pgm_header(&test_image, header);
    assert_true(result >= 0);

    /*Check it matches known good string*/
    result = strcmp(header, "P5\n1280 1024\n65535");
    assert_true(result >= 0);

    /*Ensure it writes correctly*/
}

static void test_parse_raw_data(void **state) {
    pgm_t test_image = new_pgm_image(64, 64);

    /*64 * 64 = 4096, which is: 8192 Bytes*/
    uint16_t *test_arr = malloc(sizeof(uint16_t) * 4096);  
    
    /*Fill the array with data.*/ 
    for(int i = 0; i < 4096; i++) {
        test_arr[i] = i;
    }

    int result = parse_raw_data(&test_image, test_arr);
    assert_true(result >= 4096);
     
    int one_d_idx = 0;
    for(int row = 0; row < 64; row++) {
        for(int col = 0; col < 64; col++) {
            assert_true(test_image.data_matrix.data[row][col] == test_arr[one_d_idx]);
            one_d_idx++;
        }
    }       

    free(test_arr); 
}

static void test_write_matrix(void **state) {
    char file_name[] = "/tmp/test_matrix_write.pgm";

    pgm_t test_image = new_pgm_image(64, 64);

    /*Fill the matrix with values*/
    for(int row = 0; row < 64; row++) {
        for(int col = 0; col < 64; col++) {
            test_image.data_matrix.data[col][row] = UINT16_MAX;
        }
    }       

    mode_t image_mode = S_IRUSR | S_IRWXU | S_IRGRP | S_IROTH;
    
    int fd = open(file_name, O_CREAT | O_WRONLY | image_mode);
    assert_true(0 <= fd);
    
    int written = write_matrix(&test_image, &fd);
    assert_true(written >= 8192);

    int result = close(fd);
    assert_true(0 <= result);

    /*Confirm the written contents*/
    fd = open(file_name, O_RDONLY);
    char rbuf[8192]; 
    size_t read_bytes = read(fd, rbuf, 4096);   
    assert_true(read_bytes > 0);  

    close(fd);

    /*Clean up the file*/
    remove(file_name);
}

static void test_save_pgm_image(void **state) {
    char s[] = "/tmp/test_image.pgm";

    pgm_t test_image = new_pgm_image(1280, 1024);
    
    char* file_contents = malloc(sizeof(uint16_t) * 1280 * 1024);

    int result = save_pgm_image(&test_image, s); 
    assert_true(result == 0);

    //now check if the image file exists by opening it.
    int fd = open(s, O_RDONLY);

    //Check if it 1.) Exists, 2.) Opens without issue.
    if(fd < 0) {
        assert_true(0);
    }
    
    int close_result = close(fd);
    assert_true(0 <= close_result);

    free(file_contents);

    /*Now remove the image file.*/
    remove(s);
}

/*
 * This test will draw a white outlined black square
 * You should open the image manually to verify
 */
static void test_doodle_box(void **state) {
    char s[] = "/tmp/test_doodle_box.pgm";

    pgm_t test_image = new_pgm_image(32, 32);

    /*Modify image to have full contrast in square*/
    for(int i = 0; i < 32; i++){
        test_image.data_matrix.data[0][i] = UINT16_MAX;
        test_image.data_matrix.data[31][i] = UINT16_MAX;
        test_image.data_matrix.data[i][0] = UINT16_MAX;
        test_image.data_matrix.data[i][31] = UINT16_MAX;
    }
    
    int result = save_pgm_image(&test_image, s); 
    assert_true(result == 0);

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
            assert_true(my_matrix.data[row][col] == 0);
        }
    }
}

static void test_swap_u16_endian(void **stat) {
    uint16_t chunk = 0x00FF;
    swap_u16_endian(&chunk);
    assert_true(chunk == 0xFF00);

    chunk = 0xAAFF;
    swap_u16_endian(&chunk);
    assert_true(chunk == 0xFFAA);

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
        cmocka_unit_test(test_build_pgm_header),
        cmocka_unit_test(test_parse_raw_data),
        cmocka_unit_test(test_write_matrix),
        cmocka_unit_test(test_save_pgm_image),
        cmocka_unit_test(test_doodle_box),
        cmocka_unit_test(test_2dmatrix_struct),
        cmocka_unit_test(test_clear_matrix),
        cmocka_unit_test(test_swap_u16_endian),

    }; 
    return cmocka_run_group_tests(tests, NULL, NULL);
}
