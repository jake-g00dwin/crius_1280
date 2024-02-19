#include <fcntl.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>

#include "camera_handler.h"
#include "camera_test_wrap.h"

uint16_t paImage[IRIMAGE_NBPIXELS*2];
matrix_t frame_matrix = { MAX_2D_ROWS, MAX_2D_COLS, {{0}}};

int32_t paMeta[135];

bool stop = false;
bool buffer_filled = false;



void paimage_address(int* p)
{
    p = (int*)&paImage;
}


void print_paimage(void)
{
    //printf("paImage[]:\n");
    for(int i = 0; i < (IRIMAGE_NBPIXELS*2); i++){
        //printf("%u, ", ((uint16_t*)paImage)[i]);
    }
        
}


void clear_paimage(void)
{
    for(int i = 0; i < IRIMAGE_NBPIXELS*2; i++){
        paImage[i] = 0;
    }
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


int close_camera(HANDLE camera_handle)
{
    eDALProxy1280_12USBErr err = Proxy1280_12USB_DisconnectFromModule(camera_handle);
    return err;
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
    //printf("name: '%s'\n", name);
    fflush(stdout);

    if(fps > MAX_FPS || fps < MIN_FPS) {
        //printf("Invalid fps parameter: %f, defaulting to 30\n", fps);
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
                //printf("Invalid agc value: %u, defaulting to noAGC\n", agc);
                agc_val = eNoAGC;
                break;
    }

    /*See how many devices are attached.*/
    int num_devices = num_attached();
    if(num_devices < 1){
        //printf("No devices found!\n");
        return NULL;
    }
    //printf("Found # device: %d\n", num_devices);
    fflush(stdout);

    /*connect to module(camera)*/
    eDALProxy1280_12USBErr connect_result = Proxy1280_12USB_ConnectToModule(0, &camera_handle);
    if(connect_result != eProxy1280_12USBSuccess)
    {
        //printf("Error on connection attempt: %s\n", Proxy1280_12USB_GetErrorString(connect_result)); 
        return NULL;
    }

    //printf("Camera handle ptr: %p\n", camera_handle);

    /*Set the configuration*/
    //printf("Setting the camera parameters...\n");
    Proxy1280_12USB_SetNUCProcessing(camera_handle, BP, nuc);
    Proxy1280_12USB_SetShutterLessProcessing(camera_handle, SL);
    Proxy1280_12USB_SetFloatFeature(camera_handle, efFrameRate, fps);
    Proxy1280_12USB_SetAGCProcessing(camera_handle, agc_val);

    for(int i = 0; i < NUM_TEST_FRAMES; i++){
        res  = Proxy1280_12USB_GetImage(camera_handle, paImage, paMeta, GETIMAGE_TIMEOUT);
        if(res != 0){
            return NULL;
        }
        ////printf("Im: %s\n", Proxy1280_12USB_GetErrorString(res));
    }

    return camera_handle;
}


/*
 * ############################
 * Matrix Helpers
 * ############################
 */ 


matrix_t *get_matrix_buffer(void)
{
    return &frame_matrix;
}


void clear_matrix(void)
{
    for (int row = 0; row < frame_matrix.num_rows; row++) {
        for (int col =0; col  < frame_matrix.num_cols; col++) {
           frame_matrix.data[row][col] = 0; 
        }
    }
}


void rotate_matrix_90(matrix_t *m)
{
    int temp;

    // Transpose the matrix
    for (int i = 0; i < m->num_rows; i++) {
        for (int j = i + 1; j < m->num_cols; j++) {
            temp = m->data[i][j];
            m->data[i][j] = m->data[j][i];
            m->data[j][i] = temp;
        }
    }


    // Reverse each row
    for (int i = 0; i < m->num_rows; i++) {
        for (int j = 0; j < m->num_cols / 2; j++) {
            temp = m->data[i][j];
            m->data[i][j] = m->data[i][m->num_cols - 1 - j];
            m->data[i][m->num_cols - 1 - j] = temp;
        }
    }
}


void rotate_matrix_180(matrix_t *m)
{
    rotate_matrix_90(m);
    rotate_matrix_90(m);
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
        //printf("Error: %s\n", Proxy1280_12USB_GetErrorString(err)); 
        return (int) err;
    }

    err = Proxy1280_12USB_GetImage(camera_handle, paImage, paMeta, GETIMAGE_TIMEOUT);

    return (int) err;
}


void print_matrix(uint16_t *v, size_t n, size_t p)
{
    for (size_t i = 0; i < n; i++) {
        for (size_t j = 0; j < p; j++) {
            //printf("%hu ", v[i * n + j]);
        }
        //printf("\n");
    }
    //printf("\n");
}


/*Changes the paImage into 2D matrix and swaps endian*/
void load_matrix_buffer(bool endian_swap) {
    int idx = 0;
    for(int rows = 0; rows < frame_matrix.num_rows; rows++){
        for(int cols = 0; cols < frame_matrix.num_cols; cols++){
            
            if(endian_swap){swap_u16_endian(&paImage[idx]);}

            frame_matrix.data[rows][cols] =  ((uint16_t *)paImage)[idx]; 
            idx++;
        } 
    }
}


//void get_frame_matrix(uint16_t *mat)
void get_frame_matrix(uint16_t *mat, size_t n, size_t p)
{
    //if (n != frame_matrix.num_rows){return;}
    //if (n != frame_matrix.num_cols){return;}

    int idx = 0;
    /*Iterate through the 2D array and set it from the passed array.*/
    for(int rows = 0; rows < frame_matrix.num_rows; rows++){
        for(int cols = 0; cols < frame_matrix.num_cols; cols++){
            mat[idx] =  frame_matrix.data[rows][cols];
            idx++;
        } 
    }
}


void get_paimage(int *arr)
{
    memcpy(arr, paImage, IRIMAGE_NBPIXELS*2);
}


/*
 * ############################
 * Calibration functions
 * ############################
 */ 



int shutter_2pts_calibration(HANDLE h, int iStage)
{
    /*Check if it's connected.*/
    eDALProxy1280_12USBErr res;

    res = Proxy1280_12USB_IsConnectToModule(h);
    if(res != eProxy1280_12USBSuccess){return res;}


    /*Start the calibration process*/
    res = Proxy1280_12USB_InitShutter2PtsCalibration(h,  iStage);
    if(res != eProxy1280_12USBSuccess){return res;}

    for(int i = 0; i < NUM_STEPS; i++){
        res = Proxy1280_12USB_StepShutter2PtsCalibration(h, iStage);
        if(res != eProxy1280_12USBSuccess){return res;} 
    }
        

    res = Proxy1280_12USB_FinishShutter2PtsCalibration(h, iStage);
    if(res != eProxy1280_12USBSuccess){return res;}


    /*Return the last returned state.*/
    return res;
}


int shutter_calibration(HANDLE h)
{
    eDALProxy1280_12USBErr res;
    
    /*Check if it's a valid connection handle*/
    res = Proxy1280_12USB_IsConnectToModule(h);
    if(res != eProxy1280_12USBSuccess){return res;}

    res = Proxy1280_12USB_InitShutterCalibration(h);
    if(res != eProxy1280_12USBSuccess){return res;}
    
    for(int i = 0; i < NUM_STEPS; i++){
        res = Proxy1280_12USB_StepShutterCalibration(h);
        if(res != eProxy1280_12USBSuccess){return res;}
    }

    res = Proxy1280_12USB_FinishShutterCalibration(h);

    return res;
}


int sl_calibration_t0(HANDLE h, int iStage)
{
    eDALProxy1280_12USBErr res;
    
    /*Check if it's a valid connectionT0 handle*/
    res = Proxy1280_12USB_IsConnectToModule(h);
    if(res != eProxy1280_12USBSuccess){return res;}

    res = Proxy1280_12USB_InitSLCalibrationT0(h, iStage);
    if(res != eProxy1280_12USBSuccess){return res;}

    for(int i = 0; i < NUM_STEPS; i++){
        res = Proxy1280_12USB_StepSLCalibrationT0(h, iStage);
        if(res != eProxy1280_12USBSuccess){return res;} 
    }
      

    res = Proxy1280_12USB_FinishSLCalibrationT0(h, iStage);

    return res;
}


int sl_calibration_t1(HANDLE h)
{
    eDALProxy1280_12USBErr res;
    
    /*Check if it's a valid connectionT1 handle*/
    res = Proxy1280_12USB_IsConnectToModule(h);
    if(res != eProxy1280_12USBSuccess){return res;}

    res = Proxy1280_12USB_InitSLCalibrationT1(h);
    if(res != eProxy1280_12USBSuccess){return res;}


    for(int i = 0; i < NUM_STEPS; i++){
        res = Proxy1280_12USB_StepSLCalibrationT1(h);
        if(res != eProxy1280_12USBSuccess){return res;}
    }

    res = Proxy1280_12USB_FinishSLCalibrationT1(h);

    return res;
}
