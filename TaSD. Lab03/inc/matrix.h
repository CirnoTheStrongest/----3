#ifndef MATRIX_H
#define MATRIX_H

#include <stdlib.h>
#include <stdio.h>
#define MAX_MATRIX_SIZE 1000

typedef struct
{
    size_t count_of_lines;
    size_t count_of_columns;
    int matrix[MAX_MATRIX_SIZE][MAX_MATRIX_SIZE];
} matrix_t;

void multiply_by_matrix(matrix_t *matrix1, matrix_t *matrix2, matrix_t *result);



#endif