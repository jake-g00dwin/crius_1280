/**
 * @file
 * @author Jake G <jakegoodwin@gorge.works>
 * @version 0.1.3.0
 *
 * @section DESCRIPTION
 * The camera handler is a simplified wrapper interface for the crius SDK
 * that automates and abstracts many of the details needed to use it 
 * behind the scenes.
 *
 * Most of the heavy lifting is abstracted to be done in C along with all the
 * interfacing with the camera's SDK. The camera_handler gives a safer interface
 * that can be used with python via the `cam.py` library file.
 */

#ifndef CAM_HANDLER
#define CAM_HANDLER


#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

/*Used for conditionally compiling with wrapped functs for pytest*/
#ifndef PYTEST
    #include "DALProxySwitchUSBDef.h"
    #include "DALProxy1280_12USB.h"
    #include "DALProxy1280_12USBDef.h"
#else
    #include "camera_test_wrap.h"
#endif


#define MAX_FPS 120
#define MIN_FPS 5
#define GETIMAGE_TIMEOUT 5000
#define WIDTH 1280
#define HEIGHT 1024
#define NUM_TEST_FRAMES 5

/*These are seprate, as differing cameras with various resolutions*/
#define MAX_2D_ROWS 1024
#define MAX_2D_COLS 1280

/*Used ad default number of steps in calibration(images taken)*/
#define NUM_STEPS   60

#define CAM_HANDLER_LIB 1
/*This is all for Windows systems compat*/
#if (defined (LINUX) || defined (__linux__))
    #ifdef CAM_HANDLER_LIB 
        #define CAM_HANDLER_API __attribute__((visibility("default")))
    #else
        #define CAM_HANDLER_API 
    #endif
#else
    #ifdef CAM_HANDLER_LIB  
        #define CAM_HANDLER_API __declspec(dllexport)
    #else
        #define CAM_HANDLER_API __declspec(dllimport)
    #endif
#endif

extern HANDLE m_Handle; 



/*AGC: Auto gain control*/
/*SL shutterless processing*/
/*BP Bad pixels corrections*/

//put the object type for python export here.


typedef struct {
    size_t num_rows; //The number of rows
    size_t num_cols; //The number of cols
    uint16_t data[MAX_2D_ROWS][MAX_2D_COLS];
}matrix_t;

CAM_HANDLER_API HANDLE init_camera(float fps, bool SL, char BP, uint8_t agc, char nuc);
CAM_HANDLER_API int close_camera(HANDLE camera_handle);
CAM_HANDLER_API int num_attached(void);

CAM_HANDLER_API int load_frame_buffer(HANDLE camera_handle);


CAM_HANDLER_API void get_paimage(int *arr);
CAM_HANDLER_API void print_paimage(void);
CAM_HANDLER_API void clear_paimage(void);

CAM_HANDLER_API void clear_matrix(void);
CAM_HANDLER_API matrix_t *get_matrix_buffer(void);
CAM_HANDLER_API void get_frame_matrix(uint16_t *mat, size_t n, size_t p);
CAM_HANDLER_API void print_matrix(uint16_t *v, size_t n, size_t p);
CAM_HANDLER_API void load_matrix_buffer(bool endian_swap);
CAM_HANDLER_API void swap_u16_endian(uint16_t *word);

CAM_HANDLER_API void paimage_address(int* p);

/*Camera calibration functions*/
CAM_HANDLER_API int shutter_2pts_calibration(HANDLE h, int iStage);
CAM_HANDLER_API int shutter_calibration(HANDLE h);


/**
 * # The T0 Shutterless Calibration function.
 *
 *  **Usage:**
 *
 *  First place a low temperture source in front of the camera.
 *
 *  Call the funciton first with `iStage` set to zero. During this time the
 *  the camera will step the camera using the `NUM_STEPS` defined at the top
 *  of the header file.
 *
 *  Once it has completed repeat the proscesss except pass `1` into the `iStage`
 *  parameter and use a hot temperature source.
 * 
 *
 * @param h, The camera's handle(is a void* with typdef).
 * @param iStage, The stage of calibration, 0 for cold 1 for hot sources.
 */
CAM_HANDLER_API int sl_calibration_t0(HANDLE h, int iStage);



/**
 * # The T1 Shutterless Calibration function.
 *  **DESC:**
 *  After running this function, it will generate shutter-less data for 
 *  FPA(Focal Plane Array) temperature T1. 
 *
 *  **Usage:**
 *  
 *  1. First place a temperture source in front of the camera.
 *  2. Call the `sl_calibration_t1(camera_handler_here)` function.
 *  3. Re-enable the needed processing options.
 *  
 *
 * @param h The camera's handle(is a void* with typdef).
 */
CAM_HANDLER_API int sl_calibration_t1(HANDLE h);


/**
 * **DESC:**
 *
 * **Usage:**
 *
 * @param h The camera's handle
 */
CAM_HANDLER_API int save_calibration(HANDLE h);


/*RE-EXPORTED FUNCTIONS*/

/**
 * **DESC:**
 * Set's the AGC value of the camera.
 *
 * **Usage:**
 *
 * @param h Camera Handle
 * @param agc Automatic gain control. Can take the values 0-4  
 */
CAM_HANDLER_API int set_agc(HANDLE h, unsigned char agc);

/**
 * **DESC:**
 * Get's the current AGC value set in the camera. 
 *
 * **Usage:**
 *
 * @param h Camera Handle
 * @param agc Automatic gain control. Can take the values 0-4  
 */
CAM_HANDLER_API int get_agc(HANDLE h, unsigned char *agc);



CAM_HANDLER_API int load_sl_current(HANDLE h);
CAM_HANDLER_API int save_sl_current(HANDLE h);

#endif /*CAMHANDLER*/
