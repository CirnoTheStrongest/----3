#ifndef VECTOR_H
#define VECTOR_H

#include <stdlib.h>

#define MAX_VECTOR_LEN 9999

typedef struct
{
    int values[MAX_VECTOR_LEN];
    size_t size;
} vector_t;

#endif