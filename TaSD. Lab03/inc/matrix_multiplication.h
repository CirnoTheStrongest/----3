#ifndef MATRIX_MULTIPLICATION_H
#define MATRIX_MULTIPLICATION_H

#include <stdio.h>
#include <string.h>
#include <errno.h>
#include "matrix_csr.h"
#include "matrix_csc.h"

void multiply_csc_by_csr_matrix(matrix_csc_t *matrix_csc, matrix_csr_t *matrix_csr, matrix_csc_t *result);

void multiply_csr_by_csc_matrix(matrix_csr_t *matrix_csr, matrix_csc_t *matrix_csc, matrix_csc_t *result);

void multiply_matrix_by_matrix(matrix_t *matrix1, matrix_t *matrix2, matrix_t *result);

#endif
