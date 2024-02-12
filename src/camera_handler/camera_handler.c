#include "camera_handler.h"

#include "DALProxy1280_12USB.h"
#include "DALProxy1280_12USBDef.h"
#include "DALProxySwitchUSBDef.h"



uint16_t paImage[IRIMAGE_NBPIXELS*2];


int init_camera(uint8_t fps, bool SL, bool BP, uint8_t agc)
{
    if(fps > MAX_FPS || fps < MIN_FPS) {
        return -1;
    }
    
   switch(agc){
        case no_agc:
                break;
        case hist:
                break;
        case local:
                break;
        case linear:
                break;
        default:
                return -1;
                break;
    }
        
    return 0;
}


int cam_self_test(void)
{
    return 1;
}
