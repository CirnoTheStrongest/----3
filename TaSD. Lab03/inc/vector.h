#ifndef VECTOR_H
#define VECTOR_H

#include <stdlib.h>
#include <errno.h>
#include <stdio.h>

#define INITIAL_SIZE 100

typedef struct
{
    int *values;
    size_t size;
    size_t max_capacity;
} vector_t;

int realloc_vector(vector_t *vector, size_t new_capacity);

int is_full(vector_t *vector);

int init_vector(vector_t *vector, size_t initial_size);

int read_vector_from_file(vector_t *vector, FILE *f);

#endif
