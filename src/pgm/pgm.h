#ifndef PGM 
#define PGM 

#include <inttypes.h>
#include <stddef.h>
#include <stdint.h>

/*This should be a power of two ideally 255 or 2^16*/
#define PIXEL_DEPTH UINT16_MAX 

#define MAX_2D_COLS 1920
#define MAX_2D_ROWS 1080 

#define WBUF_SIZE   MAX_2D_COLS * 2

typedef struct {
    size_t x; //The number of rows
    size_t y; //The number of cols
    uint16_t data[MAX_2D_ROWS][MAX_2D_COLS];
}matrix_t;

typedef struct {
    uint16_t width;
    uint16_t height;
    uint8_t val;
    matrix_t data_matrix;
}pgm_t;

void clear_matrix(matrix_t *m);

pgm_t new_pgm_image(size_t width, size_t height);
int save_pgm_image(pgm_t *image, char* pth);
int build_pgm_header(pgm_t *img, char* wbuf);
int parse_raw_data(pgm_t *img, uint16_t *arr);
int write_matrix(pgm_t *img, int *file_descriptor); 
void swap_u16_endian(uint16_t *word);


void self_test(void);




#endif
