#ifndef CAM_HANDLER
#define CAM_HANDLER

/*This should represent the number of pixels*/
//#ifndef IRIMAGE_NBPIXELS
//#define IRIMAGE_NBPIXELS 1920 * 1080
//#endif


#include <stdbool.h>
#include <stdint.h>

#define MAX_FPS 120
#define MIN_FPS 5
#define GETIMAGE_TIMEOUT 5000
#define WIDTH 1280
#define HEIGHT 1024

/*AGC: Auto gain control*/
enum agc {
    no_agc= 0,
    hist,
    local,
    linear, 
}; 

/*SL shutterless processing*/
/*BP Bad pixels corrections*/

//put the object type for python export here.


int cam_self_test(void);
int* init_camera(float fps, bool SL, bool BP, uint8_t agc, char nuc);
int close_camera(int *camera_handle);

int num_attached(void);
bool is_correct_name(void);
int connect_camera(int *camera_handle);

int load_frame_buffer();
void get_frame_matrix(uint16_t *mat);

void get_pgm_frame();
void get_meta_data();
void chagne_parameters();


#endif
