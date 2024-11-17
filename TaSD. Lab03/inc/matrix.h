#ifndef MATRIX_H
#define MATRIX_H

#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <tools.h>
#include "file.h"
#define MAX_MATRIX_SIZE 1000

typedef struct
{
    size_t count_of_lines;
    size_t count_of_columns;
    int *matrix;
} matrix_t;

int read_matrix(file_t filename, matrix_t *matrix);

void print_matrix(matrix_t *matrix);

void print_matrix_in_file(matrix_t *matrix, file_t output);

size_t get_size_of_matrix(matrix_t *matrix);

int init_matrix(matrix_t *matrix, size_t count_of_lines, size_t count_of_cols);

void free_matrix(matrix_t *matrix);

int set_value(matrix_t *matrix, size_t line, size_t col, int value);

int input_and_set_value(matrix_t *matrix);

#endif
