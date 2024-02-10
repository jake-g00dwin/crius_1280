#ifndef PGM 
#define PGM 

#include <inttypes.h>
#include <stddef.h>
#include <stdint.h>

#define MAX_2D_COLS 1920
#define MAX_2D_ROWS 1080 

typedef struct {
    size_t x; //The number of cols
    size_t y; //The number of rows
    uint16_t data[MAX_2D_COLS][MAX_2D_ROWS];
}matrix_t;

typedef struct {
    uint16_t width;
    uint16_t height;
    uint8_t val;
    matrix_t data_matrix;
}pgm_t;


void clear_matrix(matrix_t *m);


pgm_t new_pgm_image(size_t width, size_t height);
//pmg_t load_pgm_image();
//int save_pmg_image(pmg_t *image);


void self_test(void);




#endif
