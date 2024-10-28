#include "matrix.h"

void multiply_by_matrix(matrix_t *matrix1, matrix_t *matrix2, matrix_t *result)
{
    if (matrix1->count_of_columns != matrix2->count_of_lines)
    {
        puts("Умножение несогласованных матриц невозможно.");
        return;
    }

    result->count_of_lines = matrix1->count_of_lines;
    result->count_of_columns = matrix2->count_of_columns;

    for (size_t line = 0; line < result->count_of_lines; line++)
    {
        for (size_t col = 0; col < result->count_of_columns; col++)
        {
            
        }
    }
}
