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
    /*Stores a single frame in 1D array*/
    uint16_t paImage[IRIMAGE_NBPIXELS*2];

    /*Stores in PGM struct, Uses 2D array*/
    pgm_t frame = new_pgm_image(WIDTH, HEIGHT);

    printf("CMAKE FUNCTIONAL\r\n"); 

    /*check for camera device.*/


    return 0;
}
