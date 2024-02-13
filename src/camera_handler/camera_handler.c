#include "camera_handler.h"

#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <pthread.h>
#include <unistd.h>

#include "DALProxy1280_12USB.h"
#include "DALProxy1280_12USBDef.h"
#include "DALProxySwitchUSBDef.h"

#include "pgm.h"



uint16_t paImage[IRIMAGE_NBPIXELS*2];
matrix_t frame_matrix = {WIDTH, HEIGHT};
int32_t paMeta[135];
HANDLE m_Handle = NULL;
HANDLE m_HandleThread = NULL;
bool stop = false;
bool buffer_filled = false;


void stop_capture(void)
{
    stop = true;
}

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


int connect_camera(HANDLE *camera_handle)
{
    eDALProxy1280_12USBErr result_code;
    result_code = Proxy1280_12USB_ConnectToModule(0, camera_handle);

    if (result_code != eProxy1280_12USBSuccess){
        return (int) result_code;
    }
    return 0;
}

int close_camera(HANDLE *camera_handle)
{
    Proxy1280_12USB_DisconnectFromModule(camera_handle);
    return 0;
}

void *thread_load_frame_buffer(void *vargp)
{
    HANDLE *camera_handle = (HANDLE*)vargp;
    //eDALProxy1280_12USBErr *result_code = (eDALProxy1280_12USBErr*)vargp;
    //result_code = Proxy1280_12USB_GetImage(camera_handle, paImage, paMeta, GETIMAGE_TIMEOUT);
    Proxy1280_12USB_GetImage(camera_handle, paImage, paMeta, GETIMAGE_TIMEOUT);
    //if (result_code != eProxy1280_12USBSuccess){
    //    return (int) result_code;
   //}

    raw_into_matrix(&frame_matrix, paImage); 

    return NULL;
}


void *thread_1(void *pHandle)
{
    uint64_t imAvg = 0;
    eDALProxy1280_12USBErr eReturnCode;
    uint64_t iNb = 0;
    HANDLE handle = (HANDLE) pHandle;
    int exiting = 0;

    eReturnCode = Proxy1280_12USB_GetImage(handle, paImage, paMeta, GETIMAGE_TIMEOUT);
    do{
        //get image
        eReturnCode = Proxy1280_12USB_GetImage(handle, paImage, paMeta, GETIMAGE_TIMEOUT);
        printf("Im %lu : %s\n", iNb, Proxy1280_12USB_GetErrorString(eReturnCode));
        if (eReturnCode == eProxy1280_12USBCommFailed)
        {
            printf("Communication Lost with the USB device.Exiting...\n");
            exiting = 1;
            break;
        }

        //make avg of pixel values
        for(int i=0; i<(IRIMAGE_NBPIXELS); i++)
        {
            imAvg += ((uint16_t*)paImage)[i];
        }

        unsigned short *paMeta_ushort;
        paMeta_ushort = (unsigned short*)(paMeta+IRIMAGE_META_COUNTER);
        printf("Image %lu Framecounter %d, Avg val: %lu\n", iNb, *paMeta_ushort, (imAvg/(IRIMAGE_NBPIXELS)));
        imAvg = 0;
        iNb++;
    }while(!stop);

    if (eReturnCode == eProxy1280_12USBSuccess)
    {
        buffer_filled = true;
        //int fd = open("imgRAW.bin", O_CREAT | O_WRONLY);
        //write(fd, paImage, IRIMAGE_NBPIXELS*2);
        //close(fd);
    }
    Proxy1280_12USB_DisconnectFromModule(handle);
    handle = NULL;

    if (exiting) {
        exit(EXIT_FAILURE);
    }

    pthread_exit(NULL);
}

int load_frame_buffer(HANDLE *camera_handle)
{
    pthread_t thread_id;
    pthread_create(&thread_id, NULL, thread_1, (void*)camera_handle);

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

bool is_buffer_ready(void)
{
    return buffer_filled;
}

HANDLE* init_camera(float fps, bool SL, bool BP, uint8_t agc, char nuc)
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
    //if(num_attached() <= 0){return NULL;}

    /*Check for the correct name*/
    //if(is_correct_name() != true){return NULL;}

    /*connect to module(camera)*/
    if( connect_camera(&camera_handle) != 0){return NULL;}

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

