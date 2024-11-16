#include "vector.h"

int realloc_vector(vector_t *vector, size_t new_capacity)
{
    int *tmp = realloc(vector->values, new_capacity * sizeof(int));
    if (!tmp)
        return ENOMEM;

    vector->values = tmp;
    vector->max_capacity = new_capacity;
    return EXIT_SUCCESS;
}

int is_full(vector_t *vector)
{
    if (vector->size == vector->max_capacity)
        return 1;
    return 0;
}

int init_vector(vector_t *vector, size_t initial_size)
{
    vector->values = malloc(initial_size * sizeof(int));
    if (!vector->values)
        return ENOMEM;

    vector->max_capacity = initial_size;
    vector->size = 0;

    return EXIT_SUCCESS;
}

int read_vector_from_file(vector_t *vector, FILE *f)
{
    init_vector(vector, INITIAL_SIZE);

    char next_char = ' ';

    while (next_char != '\n' && !feof(f))
    {
        if (fscanf(f, "%d", &(vector->values[vector->size])) != 1)
            return EXIT_FAILURE;
        
        vector->size++;
        if (is_full(vector))
            realloc_vector(vector, vector->max_capacity * 2);
        
        next_char = fgetc(f);
    }

    return EXIT_SUCCESS;
}
