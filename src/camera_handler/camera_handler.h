#ifndef CAM_HANDLER
#define CAM_HANDLER


#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "DALProxySwitchUSBDef.h"
#include "DALProxy1280_12USB.h"
#include "DALProxy1280_12USBDef.h"

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
#define NUM_STEPS   10



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

HANDLE init_camera(float fps, bool SL, char BP, uint8_t agc, char nuc);
int close_camera(HANDLE camera_handle);
int num_attached(void);

int load_frame_buffer(HANDLE camera_handle);


void get_paimage(int *arr);
void print_paimage(void);
void clear_paimage(void);

void clear_matrix(void);
matrix_t *get_matrix_buffer(void);
void get_frame_matrix(uint16_t *mat, size_t n, size_t p);
void print_matrix(uint16_t *v, size_t n, size_t p);
void load_matrix_buffer(bool endian_swap);
void swap_u16_endian(uint16_t *word);

void paimage_address(int* p);

/*Camera calibration functions*/
int shutter_2pts_calibration(HANDLE h, int iStage);
int shutter_calibration(HANDLE h);
int sl_calibration_t0(HANDLE h, int iStage);
int sl_calibration_t1(HANDLE h);




#endif /*CAMHANDLER*/
