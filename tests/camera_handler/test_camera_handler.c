#include <fcntl.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <setjmp.h>
#include <cmocka.h>
#include <string.h>
#include <unistd.h>

//#include "DALProxy1280_12USB.h"
//#include "camera_test_wrap.h"
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
 * Init tests
 * ############################
 */ 

static void test_args_camera_init(void **state) {
    assert_true(1);
}



/*
 * ############################
 * Tests for SDK interface. 
 * ############################
 */

static void test_camera_init(void **state) {
    HANDLE my_handle = NULL;
    assert_null(my_handle);

    my_handle = init_camera(30, true, 1, eAGCLocal, 1);
    assert_non_null(my_handle);
    assert_ptr_equal(my_handle, (void*)0x12345678);

    int e = close_camera(my_handle);
    assert_true(e == 0);
}

static void test_num_attached(void **state) {
    //Proxy1280_12USB_GetModuleName
    int num = num_attached();
    assert_true(num > 0);
}

static void test_close_camera(void **state) {
    HANDLE h = NULL;
    int e = close_camera(h);  
    assert_false(e == 0);
}


HANDLE setup_camera(void){
    close_camera((void*)0x12345678);
    clear_matrix();
    clear_paimage();
    HANDLE my_handle = NULL;
    my_handle = init_camera(30, true, 1, eAGCLocal, 1);
    return my_handle;
}

void tear_down(HANDLE h){
    close_camera(h);
}

static void test_load_frame_buffer(void **state) {
    /*These cause a segfault*/
    //uint16_t fake_image[IRIMAGE_NBPIXELS*2] = {0};
    //uint16_t paimage[IRIMAGE_NBPIXELS*2] = {0};
    uint16_t fake_image[1310720] = {0};
    uint16_t paimage[1310720] = {0};
    
    /*get handle*/
    HANDLE h = setup_camera();
    assert_ptr_equal(h, (void*)0x12345678);

    /*load the test data*/
    int fd = open("../src/camera_handler/testdata.bin", O_RDONLY);
    assert_true(fd >= 0);
    read(fd, fake_image, sizeof(fake_image));
    close(fd);

    /*check for data in PA*/
    int res = load_frame_buffer(h);
    assert_true(res == 0);
    
    get_paimage((int*)paimage);

    for(int i = 0; i < 100; i++){
        assert_true(fake_image[i] == paimage[i]);
    }

    tear_down(h);
}

static void test_load_matrix_buffer(void **state)
{
    uint16_t fake_image[1310720] = {0};
    //uint16_t paimage[1310720] = {0};

    /*load the test data*/
    int fd = open("../src/camera_handler/testdata.bin", O_RDONLY);
    assert_true(fd >= 0);
    read(fd, fake_image, sizeof(fake_image));
    close(fd);

    HANDLE h = setup_camera();
    
    /*see what's in the matrix buffer first.*/
    matrix_t *mat_ptr = get_matrix_buffer();
    assert_true(mat_ptr->num_cols == 1280);
    assert_true(mat_ptr->num_rows == 1024);
    assert_true(mat_ptr->data[0][0] == 0);
    assert_true(mat_ptr->data[255][255] == 0);

    /*Okay now fill it with stuff.*/
    load_frame_buffer(h);

    /*Check that calling it doesn't throw errors*/
    load_matrix_buffer(false);


    /*Now check that it's the same as the other data*/
    int idx = 0;
    for(int row = 0; row < mat_ptr->num_rows; row++){
        for(int col = 0;col < mat_ptr->num_cols;col++){
            assert_true(fake_image[idx] == mat_ptr->data[row][col]);
            idx++;
        } 
    }

    /*chcek for reverse endian functionality*/
    load_matrix_buffer(true);
    
    uint16_t endian_val = ((fake_image[0] & 0xFF00)>>8)|((fake_image[0] & 0x00FF)<<8);
    assert_true(mat_ptr->data[0][0] == endian_val);

    tear_down(h);
}

static void test_get_frame_matrix(void **state)
{
    HANDLE h = setup_camera();
    
    uint16_t fake_image[1310720] = {0};
    uint16_t mat[1024][1280] = {0};


    load_frame_buffer(h);
    load_matrix_buffer(false);

    get_paimage((int*)fake_image);
    get_frame_matrix((uint16_t *)mat, 0, 0);
   
     
    /*Now check that it's the same as the other data*/
    int idx = 0;
    for(int row = 0; row < 1024; row++){
        for(int col = 0;col < 1280;col++){
            assert_true(fake_image[idx] == mat[row][col]);
            idx++;
        } 
    }

    tear_down(h);
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
        cmocka_unit_test(test_get_frame_matrix),
        cmocka_unit_test(test_load_matrix_buffer),
        cmocka_unit_test(test_load_frame_buffer),
        cmocka_unit_test(test_close_camera),
        cmocka_unit_test(test_num_attached),
        cmocka_unit_test(null_test_success),
    };
    cmocka_run_group_tests(init_tests, NULL,NULL);
    return cmocka_run_group_tests(tests, NULL, NULL);
}
