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
int init_camera(uint8_t fps, bool SL, bool BP, uint8_t agc);
int close_camera();

void get_pgm_frame();
void get_frame_matrix();
void get_meta_data();
void chagne_parameters();


#endif
