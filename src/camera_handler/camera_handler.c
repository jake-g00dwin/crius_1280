#include "camera_handler.h"

#include "DALProxy1280_12USB.h"
#include "DALProxy1280_12USBDef.h"
#include "DALProxySwitchUSBDef.h"

#include "pgm.h"

#include <string.h>
#include <stdbool.h>



uint16_t paImage[IRIMAGE_NBPIXELS*2];
matrix_t frame_matrix = {WIDTH, HEIGHT};


int num_attached(void)
{
    eDALProxy1280_12USBErr result_code;
    int num_cams = 0;
    result_code = Proxy1280_12USB_GetModuleCount(&num_cams);
    
    if (result_code != eProxy1280_12USBSuccess){
        return -1;
    }

    return num_cams;
}

bool is_correct_name(void) {
    char name[310] = {'\0'};
    Proxy1280_12USB_GetModuleName(0, name, 300);
    
    int result = strcmp(name, "");
    if (result < 0){
        return false;
    }
    return true;
}


int connect_camera(int *camera_handle)
{
    eDALProxy1280_12USBErr result_code;
    result_code = Proxy1280_12USB_ConnectToModule(0, (HANDLE) &camera_handle);

    if (result_code != eProxy1280_12USBSuccess){
        return (int) result_code;
    }
    return 0;
}

int close_camera(int *camera_handle)
{
    Proxy1280_12USB_DisconnectFromModule((HANDLE) camera_handle);
    return 0;
}

int load_frame_buffer(int *camera_handle)
{
    eDALProxy1280_12USBErr result_code;
    int32_t paMeta[135];

    result_code = Proxy1280_12USB_GetImage((HANDLE) camera_handle, paImage, paMeta, GETIMAGE_TIMEOUT);
    if (result_code != eProxy1280_12USBSuccess){
        return (int) result_code;
    }

    raw_into_matrix(&frame_matrix, paImage); 

    return 0;
}

void get_frame_matrix(uint16_t *mat)
{
    int idx = 0;
    /*Iterate through the 2D array and set it from the passed array.*/
    for(int rows = 0; rows < frame_matrix.y; rows++){
        for(int cols = 0; cols < frame_matrix.x; cols++){
            mat[idx] =  frame_matrix.data[rows][cols];
            idx++;
        } 
    }
}


int* init_camera(float fps, bool SL, bool BP, uint8_t agc, char nuc)
{
    HANDLE camera_handle = NULL;
    if(fps > MAX_FPS || fps < MIN_FPS) {
        return NULL;
    }
    
    if(agc > 3){
        return NULL;
    }    

    /*Defaulting for now*/
    enum eAGCProcessingValue agc_val = eNoAGC;
    
    /*See how many devices are attached.*/
    if(num_attached() <= 0){return NULL;}

    /*Check for the correct name*/
    //if(is_correct_name() != true){return NULL;}

    /*connect to module(camera)*/
    if( connect_camera((int*) &camera_handle) != 0){return NULL;}

    /*Set the configuration*/
    Proxy1280_12USB_SetNUCProcessing(camera_handle, BP, nuc);
    Proxy1280_12USB_SetShutterLessProcessing(camera_handle, SL);
    Proxy1280_12USB_SetFloatFeature(camera_handle, efFrameRate, fps);
    Proxy1280_12USB_SetAGCProcessing(camera_handle, agc_val);

    return camera_handle;
}


int cam_self_test(void)
{
    return 1;
}
