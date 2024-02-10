#include "pgm.h"

#include <stdio.h>
#include <stdlib.h>

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
