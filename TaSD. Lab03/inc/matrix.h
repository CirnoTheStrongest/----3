#ifndef MATRIX_H
#define MATRIX_H

#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include "file.h"
#define MAX_MATRIX_SIZE 1000

typedef struct
{
    size_t count_of_lines;
    size_t count_of_columns;
    int *matrix;
} matrix_t;

int read_matrix(file_t filename, matrix_t *matrix);

void print_matrix_in_file(matrix_t *matrix, file_t output);

void multiply_by_matrix(matrix_t *matrix1, matrix_t *matrix2, matrix_t *result);

#endif
