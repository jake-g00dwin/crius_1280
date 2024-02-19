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

/*
 * ###################################
 * MOCKS
 * ##################################
 */

/*Mocked globals*/
void *ptr = (void*)0x12345678;  // Example address
int camera_index = 0;
static const char name[] = "IrLugX1M3  sn:FR382312-01-001";
uint16_t fake_image[IRIMAGE_NBPIXELS*2];
bool is_connected = false;


/*
 * ############################
 * Helpers for testing
 * ############################
 */ 

bool is_valid_handle(HANDLE h)
{
    if(h != ptr || !is_connected){
        return eProxy1280_12USBHandleError;
    }
    return eProxy1280_12USBHandleError;
}

/*
 * ############################
 * Mocked functions
 * ############################
 */ 

/*Read the image file for testing form the file.*/
int load_fake_data(char *file_name)
{
    int fd = open(file_name, O_RDONLY);
    if(fd < 0){
        return fd;
    }
    read(fd, fake_image, IRIMAGE_NBPIXELS*2);
    close(fd);
    return 0;
}


void get_fake_data_address(void *ptr)
{
    ptr = (void *)fake_image;
}

const char* __wrap_Proxy1280_12USB_GetErrorString(eDALProxy1280_12USBErr paeError)
{
    switch(paeError){
        case eProxy1280_12USBSuccess:
            return "Function call Success.";
        case eProxy1280_12USBParameterError:
            return "Parameter Error";
        case eProxy1280_12USBHandleError:
            return "Function call with invalid handle";
        case eProxy1280_12USBInitFailed:
            return "Init failed.";
        case eProxy1280_12USBOpenFailed:
            return "Open connection to camera failed";
        case eProxy1280_12USBCommFailed:
            return "exchange with cam failed.";
        case eProxy1280_12USBTimeout:
            return "operation timedout before completion.";
        case eProxy1280_12USBSyncBroken:
            return "USB sync broken";
        case eProxy1280_12USBSequencingError:
            return "function call outside of correct sequencing.";
        default:
            return "NOT A VALID ERROR!";
    }
}


eDALProxy1280_12USBErr __wrap_Proxy1280_12USB_GetImage(HANDLE paHandle, unsigned short* paImage, int* paMeta, int paiTimeout)
{
    if(paHandle != ptr || !is_connected){
        return eProxy1280_12USBHandleError;
    }
    int r = load_fake_data("/tmp/testdata.bin");
    memcpy(paImage, fake_image, sizeof(fake_image));
    return r;
}


/*
 * ############################
 * Other conncetion features 
 * ############################
 */ 

eDALProxy1280_12USBErr __wrap_Proxy1280_12USB_GetModuleCount(int* paiCount)
{
    *paiCount = 1;
    return eProxy1280_12USBSuccess;
}

eDALProxy1280_12USBErr __wrap_Proxy1280_12USB_GetModuleName(int iIdx, char* paName, int iLen)
{
    if(iIdx == camera_index) {
        memcpy(paName, name, iLen);
        return eProxy1280_12USBSuccess;
    }   
    return eProxy1280_12USBHandleError;
}


eDALProxy1280_12USBErr __wrap_Proxy1280_12USB_ConnectToModule(int iIdx, HANDLE* paHandle)
{
    if(iIdx == camera_index && !is_connected) {
        *paHandle = ptr;
        is_connected = true;
        return eProxy1280_12USBSuccess;
    }
    return eProxy1280_12USBParameterError;
}


eDALProxy1280_12USBErr __wrap_Proxy1280_12USB_DisconnectFromModule(HANDLE paHandle)
{
    if(paHandle == ptr && is_connected){
        is_connected = false;
        return eProxy1280_12USBSuccess;
    }
    return eProxy1280_12USBHandleError;
}


eDALProxy1280_12USBErr __wrap_Proxy1280_12USB_IsConnectToModule(HANDLE paHandle)
{
    function_called();
    if(paHandle == ptr && is_connected){
        //printf("handle: %p\n", paHandle);
        //printf("saved_handle: %p\n", ptr);
        //printf("is_connected: %d\n", is_connected);
        return eProxy1280_12USBSuccess;
    }
    return eProxy1280_12USBHandleError;
}


/*
 * ############################
 * SETTING FEATURES 
 * ############################
 */ 

eDALProxy1280_12USBErr __wrap_Proxy1280_12USB_SetNUCProcessing(HANDLE paHandle, unsigned char paBadPixels, unsigned char paNUC)
{
    return is_valid_handle(paHandle);
}

eDALProxy1280_12USBErr __wrap_Proxy1280_12USB_SetShutterLessProcessing(HANDLE paHandle, bool bActivate)
{
    return is_valid_handle(paHandle);
}

eDALProxy1280_12USBErr __wrap_Proxy1280_12USB_SetAGCProcessing(HANDLE paHandle, unsigned char paeAGCProcessing)
{
    return is_valid_handle(paHandle);
}

eDALProxy1280_12USBErr __wrap_Proxy1280_12USB_SetFloatFeature(HANDLE paHandle, int paeFeature, float paFloat)
{
    return is_valid_handle(paHandle);
}


/*
 * ############################
 * CALIBRATION FUNCTIONS 
 * ############################
 */ 


eDALProxy1280_12USBErr __wrap_Proxy1280_12USB_AbortCalibration(HANDLE paHandle)
{
    function_called();
	return is_valid_handle(paHandle);
}



/*Shutter 2Pts calibration*/
eDALProxy1280_12USBErr __wrap_Proxy1280_12USB_InitShutter2PtsCalibration(HANDLE paHandle, unsigned int iStage)
{
    function_called();
    if(iStage != 1 && iStage != 2) {return eProxy1280_12USBParameterError;}
    if( !is_valid_handle(paHandle)) { return eProxy1280_12USBHandleError;}
    
    return eProxy1280_12USBSuccess;
}


eDALProxy1280_12USBErr __wrap_Proxy1280_12USB_StepShutter2PtsCalibration(HANDLE paHandle, unsigned int iStage)
{
    function_called();
    if(iStage != 1 && iStage != 2) {return eProxy1280_12USBParameterError;}
    if( !is_valid_handle(paHandle)) { return eProxy1280_12USBHandleError;}
    
    return eProxy1280_12USBSuccess;
}


eDALProxy1280_12USBErr __wrap_Proxy1280_12USB_FinishShutter2PtsCalibration(HANDLE paHandle,unsigned int iStage)
{
    function_called();
    if(iStage != 1 && iStage != 2) {return eProxy1280_12USBParameterError;}
    if( !is_valid_handle(paHandle)) { return eProxy1280_12USBHandleError;}
    
    return eProxy1280_12USBSuccess;
}




/*Shutter calibration*/
eDALProxy1280_12USBErr __wrap_Proxy1280_12USB_InitShutterCalibration(HANDLE paHandle)
{
    function_called();
    //check_expected_ptr(paHandle);
    if( !is_valid_handle(paHandle)) { return eProxy1280_12USBHandleError;}
    return eProxy1280_12USBSuccess;
}


eDALProxy1280_12USBErr __wrap_Proxy1280_12USB_StepShutterCalibration(HANDLE paHandle)
{
    function_called();
    if( !is_valid_handle(paHandle)) { return eProxy1280_12USBHandleError;}
    return eProxy1280_12USBSuccess;
}


eDALProxy1280_12USBErr __wrap_Proxy1280_12USB_FinishShutterCalibration(HANDLE paHandle)
{

    function_called();
    if( !is_valid_handle(paHandle)) { return eProxy1280_12USBHandleError;}
    return eProxy1280_12USBSuccess;
}



/*SL calibration*/
eDALProxy1280_12USBErr __wrap_Proxy1280_12USB_InitSLCalibrationT0(HANDLE paHandle, unsigned int iStage)
{
    function_called();
    if( !is_valid_handle(paHandle)) { return eProxy1280_12USBHandleError;}
    if(iStage != 1 && iStage != 2) {return eProxy1280_12USBParameterError;}
    return eProxy1280_12USBSuccess;
}


eDALProxy1280_12USBErr __wrap_Proxy1280_12USB_StepSLCalibrationT0(HANDLE paHandle, unsigned int iStage)
{
    function_called();
    if( !is_valid_handle(paHandle)) { return eProxy1280_12USBHandleError;}
    if(iStage != 1 && iStage != 2) {return eProxy1280_12USBParameterError;}
    return eProxy1280_12USBSuccess;
}


eDALProxy1280_12USBErr __wrap_Proxy1280_12USB_FinishSLCalibrationT0(HANDLE paHandle, unsigned int iStage)
{

    function_called();
    if( !is_valid_handle(paHandle)) { return eProxy1280_12USBHandleError;}
    if(iStage != 1 && iStage != 2) {return eProxy1280_12USBParameterError;}
    return eProxy1280_12USBSequencingError;
}



/*SL T1 Calibration*/
eDALProxy1280_12USBErr __wrap_Proxy1280_12USB_InitSLCalibrationT1(HANDLE paHandle)
{
    function_called();
    if( !is_valid_handle(paHandle)) { return eProxy1280_12USBHandleError;}
    return eProxy1280_12USBSequencingError;
}


eDALProxy1280_12USBErr __wrap_Proxy1280_12USB_StepSLCalibrationT1(HANDLE paHandle)
{
    function_called();
    if( !is_valid_handle(paHandle)) { return eProxy1280_12USBHandleError;}
    return eProxy1280_12USBSequencingError;
}


eDALProxy1280_12USBErr __wrap_Proxy1280_12USB_FinishSLCalibrationT1(HANDLE paHandle)
{
    function_called();
    if( !is_valid_handle(paHandle)) { return eProxy1280_12USBHandleError;}
    return eProxy1280_12USBSequencingError;
}




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


    expect_function_call(__wrap_Proxy1280_12USB_IsConnectToModule);

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


    expect_function_call(__wrap_Proxy1280_12USB_IsConnectToModule);


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


    expect_function_call(__wrap_Proxy1280_12USB_IsConnectToModule);
    
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


/*
 * ############################
 * Calibration tests.
 * ############################
 */ 


static void test_shutter_calibration(void **state) {
    HANDLE h = NULL; 
    is_connected = false;
    int res; /*Variable to store result/return values.*/

    /*Check it only accepts valid handles.*/
    expect_function_call(__wrap_Proxy1280_12USB_IsConnectToModule);
    
    /*Start by passing invalid handle*/
    res = shutter_calibration(h);
    assert_true(res == eProxy1280_12USBHandleError);




    /*Now test the function with good handle.*/
    h = setup_camera();
    assert_true(h == ptr);


    /*CHeck it calls the correct functions.*/
    expect_function_call(__wrap_Proxy1280_12USB_IsConnectToModule);
    expect_function_call(__wrap_Proxy1280_12USB_InitShutterCalibration);
    expect_function_call(__wrap_Proxy1280_12USB_StepShutterCalibration);
    expect_function_call(__wrap_Proxy1280_12USB_FinishShutterCalibration);

    /*Check it's called with the correct parameters.*/


    shutter_calibration(h);

    tear_down(h); 
}


static void test_2pts_shutter_calibration(void **state) {  

    HANDLE h = NULL; 
    is_connected = false;
    
    expect_function_call(__wrap_Proxy1280_12USB_IsConnectToModule);
    int res = shutter_2pts_calibration(h);
    assert_true(res != eProxy1280_12USBSuccess);

    h = setup_camera();

    /*Check against the saved handle*/
    assert_true(h == ptr);

    expect_function_call(__wrap_Proxy1280_12USB_IsConnectToModule);
    expect_function_call(__wrap_Proxy1280_12USB_InitShutter2PtsCalibration);
    expect_function_call(__wrap_Proxy1280_12USB_StepShutter2PtsCalibration);
    expect_function_call(__wrap_Proxy1280_12USB_FinishShutter2PtsCalibration);

    res = shutter_2pts_calibration(h);

   
   tear_down(h); 
}


static void test_sl_t0_calibration(void **state) {
 
    HANDLE h = NULL; 
    is_connected = false;
    int iStage = 0;
    int res;

    expect_function_call(__wrap_Proxy1280_12USB_IsConnectToModule);
    res = sl_t0_calibrationT0(h, iStage);
    assert_true(res != eProxy1280_12USBSuccess);
}


static void test_sl_t0_cal_low_temp(void **state) {

    HANDLE h = NULL; 
    is_connected = false;
    int iStage = 0;
    int res;


    h = setup_camera();

    expect_function_call(__wrap_Proxy1280_12USB_IsConnectToModule);
    expect_function_call(__wrap_Proxy1280_12USB_InitSLCalibrationT0);
    expect_function_call(__wrap_Proxy1280_12USB_StepSLCalibrationT0);
    expect_function_call(__wrap_Proxy1280_12USB_FinishSLCalibrationT0);

    iStage = 1;
    res = sl_t0_calibrationT0(h, iStage);

    assert_true(res == eProxy1280_12USBSequencingError);

    tear_down(h);
}

static void test_sl_t0_cal_high_temp(void **state) {

    HANDLE h = NULL; 
    is_connected = false;
    int iStage = 0;
    int res;


    h = setup_camera();

    expect_function_call(__wrap_Proxy1280_12USB_IsConnectToModule);
    expect_function_call(__wrap_Proxy1280_12USB_InitSLCalibrationT0);
    expect_function_call(__wrap_Proxy1280_12USB_StepSLCalibrationT0);
    expect_function_call(__wrap_Proxy1280_12USB_FinishSLCalibrationT0);

    iStage = 2;
    res = sl_t0_calibrationT0(h, iStage);

    assert_true(res == eProxy1280_12USBSequencingError);

    tear_down(h);
}


static void test_fast_shutter_calibration(void **state) {
   assert_false(0);
}



int main(void)
{

    const struct CMUnitTest calibration_tests[] = {
        cmocka_unit_test(test_sl_t0_cal_high_temp),
        cmocka_unit_test(test_sl_t0_cal_low_temp),
        cmocka_unit_test(test_sl_t0_calibration),
        cmocka_unit_test(test_shutter_calibration),
        cmocka_unit_test(test_fast_shutter_calibration),
        cmocka_unit_test(test_2pts_shutter_calibration),
    };

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
    cmocka_run_group_tests(tests, NULL, NULL);
    return cmocka_run_group_tests(calibration_tests, NULL, NULL);
}
