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
#include "pgm.h"

/*
 * ############################
 * DEFINES AND MACROS
 * ############################
 */ 


#define DEBUG  1

#if DEBUG == 1
#define debug(data, data_len) printf(data, data_len)
#else
#define debug(data, data_len)
#endif



#define GETIMAGE_TIMEOUT 5000

#ifndef WIDTH
#define WIDTH 1280
#endif

#ifndef HEIGHT
#define HEIGHT 1080
#endif



int main() {
    
    eDALProxy1280_12USBErr result_code;
    
    int num; 
    result_code = Proxy1280_12USB_GetModuleCount(&num);
    //int num = num_attached();
    printf("number attached: %d\n", num);
    printf("result_code: %d", (int)result_code);
 
    char name[310] = {'\0'}; 
    Proxy1280_12USB_GetModuleName(0, name, 300);
    printf("name: %s", name);

    HANDLE cam = NULL; 
    result_code = Proxy1280_12USB_ConnectToModule(0, &cam);
    printf("result_code: %d", result_code);
    //HANDLE cam = init_camera(30, 0, 0, 0, 0); 
    printf("cam ptr: %p\n", cam); 

    int result = load_frame_buffer();
    printf("load_frame_buffer(): %d\n", result);
    

    close_camera(&cam);

    return 0;
}
