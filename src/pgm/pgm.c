#include "pgm.h"

#include <inttypes.h>

#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>


void self_test(void)
{
    //do nothing
    return;
}

/*
 * ############################
 * MATRIX HELPERS/FUNCS 
 * ############################
 */ 

void clear_matrix(matrix_t *m)
{
    for(int row = 0; row < MAX_2D_ROWS ;row++){
        for(int col = 0; col < MAX_2D_COLS; col++){
            m->data[row][col] = 0;
        } 
    }
     
}

/*
 * ############################
 * PGM(PORTABLE GRAY FORMAT) Img 
 * ############################
 */ 

pgm_t new_pgm_image(size_t width, size_t height) {
    pgm_t img;
    img.height = height;
    img.width = width;
    clear_matrix(&img.data_matrix);
    return img; 
}


int parse_raw_data(pgm_t *img, uint16_t *arr)
{
    int array_idx= 0;

    /*Iterate through the 2D array and set it from the passed array.*/
    for(int rows = 0; rows < img->height; rows++){
        for(int cols = 0; cols < img->width; cols++){
           img->data_matrix.data[rows][cols] = arr[array_idx]; 
           array_idx++;
        } 
    }
        
    return array_idx;
}

int build_pgm_header(pgm_t *img, char* wbuf)
{   
    if(img->width <=0 || img->height <= 0){
        printf("ERROR: zero sized image!\n");
        return -1;
    }
    //int result = sprintf(wbuf, "P5\n%u %u\n%u\n", img->width, img->height, PIXEL_DEPTH);
    int result = sprintf(wbuf, "P5\n%" PRIu16 " %" PRIu16 "\n%u\n", img->width, img->height, PIXEL_DEPTH);
    return result;
}


int write_matrix(pgm_t *img, int *file_descriptor)
{

    int written_bytes = 0;

    size_t row_size = img->width * sizeof(uint16_t);

    /*Fill up the buffer*/
    for(int row = 0; row < img->height; row++) {  
        void *row_data = &img->data_matrix.data[row][0];
 
        /*Write the buffer*/
        written_bytes += write(*file_descriptor, (char*)row_data, row_size);
    }
    
    return written_bytes;
}

int save_pgm_image(pgm_t *image, char* pth)
{

    /*Set the UNIX permissions to allow RW for ownder and read otherwise.*/
    mode_t image_mode = S_IRUSR | S_IRWXU | S_IRGRP | S_IROTH;

    /*Open the file at the passed path, using POSIX open.*/
    int fd = open(pth, O_CREAT | O_WRONLY | image_mode);

    /*Check that the file handle isnt null*/
    /*If it's non-existent then make it.*/
    if(fd < 0) {
        printf("Error Number % d\n", errno);
        perror("Program");
        return fd;
    }
    
    /*Write the header info*/
    char wbuf[128] = {'\0'};
    build_pgm_header(image, wbuf);

    int header_length = strlen(wbuf); 

    int write_result = write(fd, wbuf, sizeof(char) * header_length);
 
    if(write_result < 0) {
        printf("Error: Number % d\n", errno);
        printf("Issue writing to file!\n");
        perror("Program");
        return write_result;
    } 

    /*Now write the matrix*/
    int written = write_matrix(image, &fd); 
    if(written < (image->height * image->width)) {
        perror("Program");
        return written;
    }

    /*close the file handler.*/
    int close_result = close(fd);
    
    /*return the result of the file handle being closed.*/
    return close_result;
}
