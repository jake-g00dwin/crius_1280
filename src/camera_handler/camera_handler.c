#include "camera_handler.h"

#include "DALProxy1280_12USB.h"
#include "DALProxy1280_12USBDef.h"
#include "DALProxySwitchUSBDef.h"

#include <string.h>
#include <stdbool.h>



uint16_t paImage[IRIMAGE_NBPIXELS*2];



uint8_t num_attached(void)
{
    eDALProxy1280_12USBErr result_code;
    int num_cams = 0;
    result_code = Proxy1280_12USB_GetModuleCount(&num_cams);

    if (result_code != eProxy1280_12USBSuccess){
        return 0;
    }

    return num_cams;
}

bool is_correct_name(void) {
    char name[300] = {'\0'};
    Proxy1280_12USB_GetModuleName(0, name, 300);
    
    int result = strcmp(name, "");
    if (result < 0){
        return false;
    }
    return true;
}

int init_camera(uint8_t fps, bool SL, bool BP, uint8_t agc)
{
    if(fps > MAX_FPS || fps < MIN_FPS) {
        return -1;
    }
    
    if(agc > 3){
        return -1;
    }    

    
    /*See how many devices are attached.*/
    if(num_attached() <= 0){return -1;}

    /*Check for the correct name*/
    if(correct_name() != true){return -1;}

    /*connect to module(camera)*/
    if( connect_camera() < 0){return -1;}

    /*do a self-test*/

    /*Set the configuration*/

    return 0;
}


int cam_self_test(void)
{
    return 1;
}
