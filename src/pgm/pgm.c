#include "pgm.h"

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
            m->data[col][row] = 0;
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



int build_pgm_header(pgm_t *img, char* wbuf)
{
    return 0;
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
    char wbuf[WBUF_SIZE];
    strncpy(wbuf, "P5\n\0", 4); 
    int write_result = write(fd, wbuf, sizeof(wbuf));
    

    if(write_result < 0) {
        printf("Error: Number % d\n", errno);
        printf("Issue writing to file!\n");
        perror("Program");
        return write_result;
    } 

    /*close the file handler.*/
    int close_result = close(fd);
    
    /*return the result of the file handle being closed.*/
    return close_result;
}
