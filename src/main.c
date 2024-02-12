#include <fcntl.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "pgm/pgm.h"


int main() {
    printf("CMAKE FUNCTIONAL\r\n");
   

    char src[] = "frame0.raw";
    pgm_t frame = new_pgm_image(1280, 1024);

    size_t num_bytes = sizeof(uint16_t) * 1280 * 1024;
    uint16_t* file_contents = malloc(num_bytes);

    /*Open the raw data.*/
    int fd = open(src, O_RDONLY);
   
    read(fd, &file_contents, num_bytes);

    parse_raw_data(&frame, file_contents);
    save_pgm_image(&frame, "./image.pgm");

    close(fd);
    free(file_contents);

    return 0;
}
