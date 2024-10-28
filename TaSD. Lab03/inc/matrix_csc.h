#ifndef MATRIX_CSC_H
#define MATRIX_CSC_H

#include "vector.h"

typedef struct
{
    vector_t A;
    vector_t IA;
    vector_t JA;
} matrix_csc_t;

#endif