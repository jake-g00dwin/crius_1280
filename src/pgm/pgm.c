#include "pgm.h"
#if defined (__linux__)
#include <pthread.h>
#include <unistd.h>
#endif


void self_test(void)
{
    //do nothing
    return;
}

void clear_matrix(matrix_t *m)
{
    for(int row = 0; row < MAX_2D_ROWS ;row++){
        for(int col = 0; col < MAX_2D_COLS; col++){
            m->data[col][row] = 0;
        } 
    }
     
}
