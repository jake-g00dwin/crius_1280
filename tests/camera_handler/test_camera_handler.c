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


    for(int i = 0; i < 100; i++){
        //printf("%d", fake_image[i]);
        assert_true(fake_image[i] == paimage[i]);
    }

    //get_paimage((int*)paimage);

    //for(size_t i = 0; i < IRIMAGE_NBPIXELS; i++){
    //    assert_true(paimage[i] == fake_image[i]);
   // }

    /*Check that the order is correct*/

    /*Check that it ensures good handle use*/

    close_camera(h);
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
        cmocka_unit_test(test_load_frame_buffer),
        cmocka_unit_test(test_close_camera),
        cmocka_unit_test(test_num_attached),
        cmocka_unit_test(null_test_success),
    };
    cmocka_run_group_tests(init_tests, NULL,NULL);
    return cmocka_run_group_tests(tests, NULL, NULL);
}
