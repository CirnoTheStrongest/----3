#ifndef MATRIX_CSR_H
#define MATRIX_CSR_H

#include <stdio.h>
#include <string.h>
#include <errno.h>
#include "vector.h"
#include "tools.h"
#include "matrix.h"

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

int read_matrix_csr(matrix_csr_t *matrix_csr, file_t filename);

void print_matrix_csr(matrix_csr_t *matrix);

void print_matrix_csr_vectors(matrix_csr_t *matrix);

void print_matrix_csr_vectors_in_file(matrix_csr_t *matrix, file_t filename);

int set_value_csr(matrix_csr_t *matrix, int value, size_t line, size_t col);

int get_sparceness_percent_csr(matrix_csr_t *matrix, size_t *percent);

int convert_matrix_to_csr(matrix_t *matrix, matrix_csr_t *matrix_csr);

int read_matrix_csr_as_matrix(file_t filename, matrix_csr_t *matrix_csr);

#endif
