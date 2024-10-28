#ifndef MATRIX_CSR_H
#define MATRIX_CSR_H

#include <stdio.h>
#include <string.h>
#include <errno.h>
#include "vector.h"
#include "matrix_csc.h"
#include "tools.h"

#define MAX_STR_LEN 3 * 10000 + 1

typedef struct
{
    // Массив значений
    vector_t A;
    // Массив столбцов
    vector_t JA;
    // Массив индексов JA, с какого элемента начинается строка
    vector_t IA;
} matrix_csr_t;

int read_matrix_csr(FILE *f, matrix_csr_t *matrix);

void print_matrix_csr(matrix_csr_t *matrix);

void print_matrix_csr_vectors(matrix_csr_t *matrix);

int set_value_csr(matrix_csr_t *matrix, int value, size_t line, size_t col);

int get_sparceness_percent_csr(matrix_csr_t *matrix, size_t *percent);

void multiply_by_csc_matrix(matrix_csr_t *matrix_csr, matrix_csc_t *matrix_csc);

#endif