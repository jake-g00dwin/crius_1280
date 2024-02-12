#include "camera_handler.h"

#include <stdbool.h>
#include <stdint.h>

#include "DALProxy1280_12USB.h"
#include "DALProxy1280_12USBDef.h"
#include "DALProxySwitchUSBDef.h"


//uint16_t paImage[IRIMAGE_NBPIXELS*2];


int init_camera(uint8_t fps, bool SL, bool BP, uint8_t agc)
{
    if(fps > MAX_FPS || fps < MIN_FPS) {
        return -1;
    }


    return 0;
}


int cam_self_test(void)
{
    return 1;
}
