#ifndef CAM_HANDLER
#define CAM_HANDLER

/*This should represent the number of pixels*/
//#ifndef IRIMAGE_NBPIXELS
//#define IRIMAGE_NBPIXELS 1920 * 1080
//#endif


#include <stdbool.h>
#include <stdint.h>
#include "DALProxy1280_12USB.h"

#define MAX_FPS 120
#define MIN_FPS 5
#define GETIMAGE_TIMEOUT 5000
#define WIDTH 1280
#define HEIGHT 1024
#define NUM_TEST_FRAMES 30
#define MAX_2D_ROWS 1920
#define MAX_2D_COLS 1080


extern HANDLE m_Handle; 

/*AGC: Auto gain control*/
/*SL shutterless processing*/
/*BP Bad pixels corrections*/

//put the object type for python export here.


HANDLE init_camera(float fps, bool SL, char BP, uint8_t agc, char nuc);
int close_camera(HANDLE *camera_handle);
int num_attached(void);

int load_frame_buffer(HANDLE camera_handle);
void load_matrix_buffer(bool endian_swap);
void swap_u16_endian(uint16_t *word);

void print_paimage(void);

//threaded functions.
int th_load_frame_buffer();
void get_frame_matrix(uint16_t *mat);

void *thread_1(void *pHandle);
void *thread_load_frame_buffer(void *vargp);

void stop_capture(void);
bool is_buffer_ready(void);


#endif
