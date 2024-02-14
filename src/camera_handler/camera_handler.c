#include "camera_handler.h"

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <pthread.h>
#include <unistd.h>

#include "DALProxy1280_12USB.h"
#include "DALProxy1280_12USBDef.h"
#include "DALProxySwitchUSBDef.h"

typedef struct {
    size_t x; //The number of rows
    size_t y; //The number of cols
    uint16_t data[MAX_2D_ROWS][MAX_2D_COLS];
}matrix_t;


uint16_t paImage[IRIMAGE_NBPIXELS*2];
matrix_t frame_matrix = {WIDTH, HEIGHT};
int32_t paMeta[135];

bool stop = false;
bool buffer_filled = false;



void print_paimage(void)
{
    printf("paImage[]:\n");
    for(int i = 0; i < (IRIMAGE_NBPIXELS*2); i++){
        printf("%u, ", ((uint16_t*)paImage)[i]);
    }
        
}

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
        return result_code;
    }
    return num_cams;
}

int close_camera(HANDLE *camera_handle)
{
    Proxy1280_12USB_DisconnectFromModule(camera_handle);
    return 0;
}


bool is_buffer_ready(void)
{
    return buffer_filled;
}

HANDLE init_camera(float fps, bool SL, char BP, uint8_t agc, char nuc)
{
    HANDLE camera_handle = NULL;
    enum eAGCProcessingValue agc_val = eNoAGC;
    eDALProxy1280_12USBErr res;

    char name[310] = {'\0'}; 
    Proxy1280_12USB_GetModuleName(0, name, 300);
    printf("name: '%s'\n", name);
    fflush(stdout);

    if(fps > MAX_FPS || fps < MIN_FPS) {
        printf("Invalid fps parameter: %f, defaulting to 30\n", fps);
        fps = 30;
    }
    
    switch(agc_val){
        case eNoAGC:
                agc_val = eNoAGC; 
                break;
        case eAGCEqHisto:
                agc_val = eAGCEqHisto;
                break;
        case eAGCLocal:
                agc_val = eAGCLocal;
                break;
        case eAGCLinear:
                agc_val = eAGCLinear;
                break;
        case eAGCTotal:
                agc_val = eAGCTotal;
                break;
        default:
                printf("Invalid agc value: %u, defaulting to noAGC\n", agc);
                agc_val = eNoAGC;
                break;
    }

    /*See how many devices are attached.*/
    int num_devices = num_attached();
    if(num_devices < 1){
        printf("No devices found!\n");
        return NULL;
    }
    printf("Found # device: %d", num_devices);
    fflush(stdout);

    /*connect to module(camera)*/
    eDALProxy1280_12USBErr connect_result = Proxy1280_12USB_ConnectToModule(0, &camera_handle);
    if(connect_result != eProxy1280_12USBSuccess)
    {
        printf("Error on connection attempt: %s\n", Proxy1280_12USB_GetErrorString(connect_result)); 
        return NULL;
    }

    printf("Camera handle ptr: %p\n", camera_handle);

    /*Set the configuration*/
    printf("Setting the camera parameters...\n");
    Proxy1280_12USB_SetNUCProcessing(camera_handle, BP, nuc);
    Proxy1280_12USB_SetShutterLessProcessing(camera_handle, SL);
    Proxy1280_12USB_SetFloatFeature(camera_handle, efFrameRate, fps);
    Proxy1280_12USB_SetAGCProcessing(camera_handle, agc_val);

    for(int i = 0; i < NUM_TEST_FRAMES; i++){
        res  = Proxy1280_12USB_GetImage(camera_handle, paImage, paMeta, GETIMAGE_TIMEOUT);
        printf("Im: %s\n", Proxy1280_12USB_GetErrorString(res));
    }

    /*
    int fd = open("/tmp/imgRAW.bin", O_CREAT | O_WRONLY);
    write(fd, paImage, IRIMAGE_NBPIXELS*2);
    close(fd);    
    */

    return camera_handle;
}


/*
 * ############################
 * FRAME LOADING 
 * ############################
 */


/*Swaps the order of bytes, needed for the camera*/
void swap_u16_endian(uint16_t *word)
{
    uint8_t hibyte = (uint8_t)((*word) & 0x00FF);
    uint8_t lobyte = (uint8_t)( ((*word) & 0xFF00)>>8 );

    *word = (hibyte<<8)|(lobyte);
}

/*Gets a frame and puts it into the matrix*/
int load_frame_buffer(HANDLE camera_handle) {
    /*Load the image*/
    eDALProxy1280_12USBErr err;
    err = Proxy1280_12USB_IsConnectToModule(camera_handle); 
    if(err != eProxy1280_12USBSuccess){
        printf("Error: %s\n", Proxy1280_12USB_GetErrorString(err)); 
        return (int) err;
    }

    err = Proxy1280_12USB_GetImage(camera_handle, paImage, paMeta, GETIMAGE_TIMEOUT);

    return (int) err;
}

/*Changes the paImage into 2D matrix and swaps endian*/
void load_matrix_buffer() {
    int idx = 0;
    for(int rows = 0; rows < frame_matrix.y; rows++){
        for(int cols = 0; cols < frame_matrix.x; cols++){
            swap_u16_endian(&paImage[idx]);
            frame_matrix.data[rows][cols] =  paImage[idx]; 
            idx++;
        } 
    }
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


/*
 * ############################
 * Threaded frame loading 
 * ############################
 */ 
void *thread_load_frame_buffer(void *vargp)
{
    HANDLE *camera_handle = (HANDLE*)vargp;
    //eDALProxy1280_12USBErr *result_code = (eDALProxy1280_12USBErr*)vargp;
    //result_code = Proxy1280_12USB_GetImage(camera_handle, paImage, paMeta, GETIMAGE_TIMEOUT);
    Proxy1280_12USB_GetImage(camera_handle, paImage, paMeta, GETIMAGE_TIMEOUT);
    //if (result_code != eProxy1280_12USBSuccess){
    //    return (int) result_code;
   //}

    //raw_into_matrix(&frame_matrix, paImage); 

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
    }while(!stop && iNb < NUM_TEST_FRAMES);

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

int th_load_frame_buffer(HANDLE *camera_handle)
{
    pthread_t thread_id;
    pthread_create(&thread_id, NULL, thread_1, (void*)camera_handle);

    return 0;
}

