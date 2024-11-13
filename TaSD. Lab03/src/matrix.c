#include "matrix.h"

// матрица хранится как одномерный массив

void print_matrix_in_file(matrix_t *matrix, file_t output)
{
    FILE *f = fopen(output, "w");

    fprintf(f, "%lu %lu\n", matrix->count_of_lines, matrix->count_of_columns);
    for (size_t i = 0; i < matrix->count_of_lines; i++)
    {
        for (size_t j = 0; j < matrix->count_of_columns; j++)
        {
            fprintf(f, "%d ", *(matrix->matrix + i * matrix->count_of_columns + j));
        }
        fprintf(f, "\n");
    }

    fclose(f);
}

int read_matrix(file_t filename, matrix_t *matrix)
{
    FILE *f = fopen(filename, "r");
    size_t n, m;

    if (fscanf(f, "%lu %lu", &n, &m) != 2)
    {
        fclose(f);
        return EIO;
    }

    matrix->matrix = malloc(sizeof(int) * (n * m + 2));

    if (!(matrix->matrix))
    {
        fclose(f);
        return ENOMEM;
    }

    matrix->count_of_lines = n;
    matrix->count_of_columns = m;
    
    for (size_t i = 0; i < n; i++)
    {
        for (size_t j = 0; j < m; j++)
        {
            if (!fscanf(f, "%d", matrix->matrix + m * i + j))
            {
                fclose(f);
                free(matrix->matrix);
                return EIO;
            }
        }
    }

    fclose(f);
    return EXIT_SUCCESS;
}
