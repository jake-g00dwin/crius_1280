/*
 * Author: Jake G
 * Date: 2023
 * filename: main.c
 * Description: Acts as interface to C API for camera for python calls.
 */
#include <fcntl.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/*Needed for the camera sdks*/
#include <stdbool.h>

/*The Camera SDK*/
#include <DALProxy1280_12USB.h>
#include <DALProxy1280_12USBDef.h>
#include <DALProxySwitchUSBDef.h>

/*The pgm image functions structs, used for matrix ops at the moment*/
#include "camera_handler.h"

/*
 * ############################
 * DEFINES AND MACROS
 * ############################
 */ 

#define GETIMAGE_TIMEOUT 5000

#ifndef WIDTH
#define WIDTH 1280
#endif

#ifndef HEIGHT
#define HEIGHT 1080
#endif

//using the extenrally linked global in camera_handler
HANDLE m_Handle = NULL;

int main() {
    HANDLE cam = NULL;
    cam = NULL; 
    eDALProxy1280_12USBErr result_code;
    
    int num; 
    result_code = Proxy1280_12USB_GetModuleCount(&num);
    //int num = num_attached();
    printf("number attached: %d\n", num);
    printf("result_code: %d\n", (int)result_code);
 
    char name[310] = {'\0'}; 
    Proxy1280_12USB_GetModuleName(0, name, 300);
    printf("name: %s\n", name);

    //HANDLE cam = NULL; 
    printf("initalizing camera(may take a few moments)\n");
    cam = init_camera(30, true, 1, 2, 1); 
    //result_code = Proxy1280_12USB_ConnectToModule(0, &cam);
    printf("result_code: %d\n", result_code);
    printf("cam ptr: %p\n", cam); 
    
    if(cam == NULL){
        printf("Handle is null\n");
        return -1;
    }

    sleep(2);

    int result = load_frame_buffer(&cam);
    load_matrix_buffer();
    printf("load_frame_buffer(): %d\n", result);
    
    uint16_t frame_matrix[HEIGHT][WIDTH];
    get_frame_matrix((uint16_t*)&frame_matrix);

    for(int row = 0; row < 16; row++){
        for(int col = 0; col < 16; col++){
            printf("element: %d", frame_matrix[row][col]);
        }
    }

    printf("Disconnecting from camera!\n");
    close_camera(&cam);

    return 0;
}
