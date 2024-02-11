#include "pgm.h"

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>


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


int save_pmg_image(pgm_t *image, char* pth)
{
    int result = 0;
    
    /*Open the file at the passed path.*/
    int fd = open(pth, O_CREAT | O_WRONLY);

    /*Check that the file handle isnt null*/
    if(fd == -1) {
        printf("Error Number % d\n", errno);
        perror("Program");
        result = -1;
    }

    /*close the file handler.*/

    /*return the result of the file handle being closed.*/

    return result; 
}
