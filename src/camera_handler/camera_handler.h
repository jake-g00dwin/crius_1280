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

extern HANDLE m_Handle; 

/*AGC: Auto gain control*/
/*SL shutterless processing*/
/*BP Bad pixels corrections*/

//put the object type for python export here.


int cam_self_test(void);
HANDLE init_camera(float fps, bool SL, char BP, uint8_t agc, char nuc);
int close_camera(HANDLE *camera_handle);

int num_attached(void);
bool is_correct_name(void);
int connect_camera(HANDLE *camera_handle);

int load_frame_buffer();
void get_frame_matrix(uint16_t *mat);
void *thread_1(void *pHandle);
void *thread_load_frame_buffer(void *vargp);

void stop_capture(void);
bool is_buffer_ready(void);

void get_pgm_frame();
void get_meta_data();
void chagne_parameters();


#endif
