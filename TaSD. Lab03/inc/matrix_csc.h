#ifndef MATRIX_CSC_H
#define MATRIX_CSC_H

#include <stdio.h>
#include <string.h>
#include <errno.h>
#include "vector.h"
#include "tools.h"
#include "matrix.h"

typedef struct
{
    // Массив значений
    vector_t A;
    // Массив строк
    vector_t IA;
    // Массив индексов IA, с какого элемента начинается столбец
    vector_t JA;
} matrix_csc_t;

int read_matrix_csc(matrix_csc_t *matrix_csc, file_t filename);

void print_matrix_csc(matrix_csc_t *matrix);

void print_matrix_csc_vectors(matrix_csc_t *matrix);

void print_matrix_csc_vectors_in_file(matrix_csc_t *matrix, file_t filename);

int set_value_csc(matrix_csc_t *matrix, int value, size_t line, size_t col);

int get_sparceness_percent_csc(matrix_csc_t *matrix, size_t *percent);

int convert_matrix_to_csc(matrix_t *matrix, matrix_csc_t *matrix_csc);

int read_matrix_csc_as_matrix(file_t filename, matrix_csc_t *matrix_csc);

int init_matrix_csc(matrix_csc_t *matrix_csc, size_t initial_A_size, size_t initial_JA_size);

int is_matrix_csc_full(matrix_csc_t *matrix_csc);

int realloc_matrix_csc(matrix_csc_t *matrix_csc);

void free_matrix_csc(matrix_csc_t *matrix_csc);

size_t get_size_of_matrix_csc(matrix_csc_t *matrix_csc);

#endif
