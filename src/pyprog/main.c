// 
// main.c
// 
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>

void print_u16(uint16_t *v, size_t n)
{
    for (size_t i = 0; i < n; i++)
    {
        printf("%hu ", v[i]);
    }
    printf("\n");
}

void print_array(double *v, size_t n)
{
    for (size_t i = 0; i < n; i++)
    {
        printf("%f ", v[i]);
    }
    printf("\n");
}

void print_u16_mat(uint16_t *v, size_t rows, size_t cols)
{
    for (int i= 0; i < (rows * cols); i++) {
            printf( " %hu ", ((uint16_t*)v)[i]);
    }
}

void print_matrix(uint16_t *v, size_t n, size_t p)
{
    for (size_t i = 0; i < n; i++) {
        for (size_t j = 0; j < p; j++) {
            printf("%hu ", v[i * n + j]);
        }
        printf("\n");
    }
    printf("\n");
}


void clear_u16_mat(uint16_t *v, size_t n, size_t p)
{
    for (size_t i = 0; i < n; i++) {
        for (size_t j = 0; j < p; j++) {
            v[i * n + j] = 0;
            printf("%hu ", v[i * n + j]);
        }
        printf("\n");
    }
    printf("\n");
}


int main()
{
}

