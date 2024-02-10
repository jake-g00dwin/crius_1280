#ifndef PGM 
#define PGM 

#include <inttypes.h>
#include <stddef.h>
#include <stdint.h>

#define MAX_2D_COLS 1920
#define MAX_2D_ROWS 1080 

typedef struct {
    uint16_t width;
    uint16_t height;
    uint8_t val;
}pgm_t;

typedef struct {
    size_t x; //The number of cols
    size_t y; //The number of rows 
}matrix_t;

void self_test(void);



#endif
