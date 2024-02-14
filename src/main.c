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
    uint16_t frame_matrix[HEIGHT][WIDTH];
      
    printf("initalizing camera(may take a few moments)\n");
    HANDLE cam = init_camera(30, true, 1, eAGCLocal, 1); 
    
    if(cam == NULL){
        printf("Handle is null\n");
        return -1;
    }


    //print_paimage();
    //int result = load_frame_buffer(&cam);
    //printf("load_frame_buffer(): %d\n", result);
   
    load_matrix_buffer();
    get_frame_matrix(&frame_matrix[0][0]);

    printf("Printing 16 , 16 elements from matrix...\n");
    for(int row = 0; row < 16; row++){
        for(int col = 0; col < 16; col++){
            printf("%d, ", frame_matrix[row][col]);
        }
        printf("\n");
    }

    printf("Disconnecting from camera!\n");
    close_camera(&cam);

    return 0;
}
