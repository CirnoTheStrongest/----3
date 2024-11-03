#ifndef MATRIX_CSC_H
#define MATRIX_CSC_H

#include <stdio.h>
#include "vector.h"

typedef struct
{
    // Массив значений
    vector_t A;
    // Массив строк
    vector_t IA;
    // Массив индексов IA, с какого элемента начинается столбец
    vector_t JA;
} matrix_csc_t;

int read_matrix_csc(FILE *f, matrix_csc_t *matrix);

void print_matrix_csc(matrix_csc_t *matrix);

void print_matrix_csc_vectors(matrix_csc_t *matrix);

int set_value_csc(matrix_csc_t *matrix, int value, size_t line, size_t col);

int get_sparceness_percent_csc(matrix_csc_t *matrix, size_t *percent);

#endif