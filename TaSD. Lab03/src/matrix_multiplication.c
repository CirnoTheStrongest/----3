#include "matrix_multiplication.h"

/*
Функции для умножения csc-матрицы на csr-матрицу
*/

static void multiply_csc_col_by_csr_line(matrix_csc_t *matrix_csc, matrix_csr_t *matrix_csr, size_t col, size_t line, int *result)
{
    *result = 0;
    size_t cur_elem_in_col = matrix_csc->JA.values[col];
    size_t col_end = matrix_csc->JA.values[col + 1];

    size_t cur_elem_in_line = matrix_csr->IA.values[line];
    size_t line_end = matrix_csr->IA.values[line + 1];

    size_t cur_line;
    size_t cur_col;

    int cur_col_value;
    int cur_line_value;

    while (cur_elem_in_col < col_end && cur_elem_in_line < line_end)
    {
        cur_line = matrix_csc->IA.values[cur_elem_in_col];
        cur_col = matrix_csr->JA.values[cur_elem_in_line];

        cur_col_value = matrix_csc->A.values[cur_elem_in_col];
        cur_line_value = matrix_csr->A.values[cur_elem_in_line];

        if (cur_line == cur_col)
        {
            *result += cur_col_value * cur_line_value;
            cur_elem_in_col++;
            cur_elem_in_line++;
        }
        else if (cur_line > cur_col)
            cur_elem_in_col++;
        else
            cur_elem_in_line++;
    }
}

void multiply_csr_by_csc_matrix(matrix_csr_t *matrix_csr, matrix_csc_t *matrix_csc, matrix_csc_t *result)
{
    result->A.size = 0;
    result->JA.size = 0;
    result->IA.size = 0;
    result->JA.values[0] = 0;

    int cur_elem;

    for (size_t cur_col = 0; cur_col < matrix_csc->JA.size; cur_col++)
    {
        result->JA.values[result->JA.size + 1] = result->JA.values[result->JA.size];
        result->JA.size++;

        for (size_t cur_line = 0; cur_line < matrix_csr->IA.size; cur_line++)
        {
            multiply_csc_col_by_csr_line(matrix_csc, matrix_csr, cur_col, cur_line, &cur_elem);

            if (cur_elem != 0)
            {
                result->A.values[result->A.size++] = cur_elem;
                result->JA.values[result->JA.size]++;
                result->IA.values[result->IA.size++] = cur_line;
            }
        }
    }
}

/*
Функции для умножения csc-матрицы на csr-матрицу
*/

static void multiply_csr_col_by_csc_line(matrix_csc_t *matrix_csc, matrix_csr_t *matrix_csr, size_t line, size_t col, int *result)
{
    *result = 0;

    size_t cur_line = -1;
    size_t cur_col = -1;

    // для csc
    // начало 1 стобца
    size_t cur_elem_in_col;
    // конец 1 столбца
    size_t col_end;
    //ищем поочередно в каждом столбце строку line, перемножаем с соответствующим элементом столбца col в csr

    // для csr
    // начало 1 строки
    size_t cur_elem_in_line;
    // конец 1 строки
    size_t line_end;;
    // ищем поочередно в каждой строке столбец col, перемножаем с соответствующим элементом строки line в csc

    while (cur_col + 1 < matrix_csc->JA.size && cur_line + 1 < matrix_csr->IA.size)
    {
        cur_col++;
        cur_line++;

        cur_elem_in_col = matrix_csc->JA.values[cur_col];
        col_end = matrix_csc->JA.values[cur_col + 1];

        cur_elem_in_line = matrix_csr->IA.values[cur_line];
        line_end = matrix_csr->IA.values[cur_line + 1];

        while ((size_t) matrix_csc->IA.values[cur_elem_in_col] != line && cur_elem_in_col < col_end)
            cur_elem_in_col++;
        if (cur_elem_in_col == col_end)
            continue;;
        
        while ((size_t) matrix_csr->JA.values[cur_elem_in_line] != col && cur_elem_in_line < line_end)
            cur_elem_in_line++;
        if (cur_elem_in_line == line_end)
            continue;;

        *result += matrix_csc->A.values[cur_elem_in_col] * matrix_csr->A.values[cur_elem_in_line];
    }
    
}

void multiply_csc_by_csr_matrix(matrix_csc_t *matrix_csc, matrix_csr_t *matrix_csr, matrix_csc_t *result)
{
    result->A.size = 0;
    result->JA.size = 0;
    result->IA.size = 0;
    result->JA.values[0] = 0;

    int cur_elem;

    for (size_t cur_col = 0; cur_col < (size_t) find_max(matrix_csr->JA.values, matrix_csr->JA.size) + 1; cur_col++)
    {
        result->JA.values[result->JA.size + 1] = result->JA.values[result->JA.size];
        result->JA.size++;

        for (size_t cur_line = 0; cur_line < (size_t) find_max(matrix_csc->IA.values, matrix_csc->IA.size) + 1; cur_line++)
        {
            multiply_csr_col_by_csc_line(matrix_csc, matrix_csr, cur_line, cur_col, &cur_elem);

            if (cur_elem != 0)
            {
                result->A.values[result->A.size++] = cur_elem;
                result->JA.values[result->JA.size]++;
                result->IA.values[result->IA.size++] = cur_line;
            }
        }
    }
}

/*
Функции для умножения матриц в обычном виде
*/

static void multiply_matrix_line_by_matrix_col(matrix_t *matrix1, size_t line, matrix_t *matrix2, size_t col, int *result)
{
    *result = 0;

    for (size_t i = 0; i < matrix1->count_of_columns; i++)
        *result += matrix1->matrix[matrix1->count_of_columns * line + i] * matrix2->matrix[matrix2->count_of_columns * i + col];
}

void multiply_matrix_by_matrix(matrix_t *matrix1, matrix_t *matrix2, matrix_t *result)
{
    if (matrix1->count_of_columns != matrix2->count_of_lines)
    {
        puts("Умножение несогласованных матриц невозможно.");
        return;
    }

    result->matrix = malloc(sizeof(int) * (matrix1->count_of_lines * matrix2->count_of_columns + 2));

    result->count_of_lines = matrix1->count_of_lines;
    result->count_of_columns = matrix2->count_of_columns;

    for (size_t line = 0; line < result->count_of_lines; line++)
    {
        for (size_t col = 0; col < result->count_of_columns; col++)
        {
            multiply_matrix_line_by_matrix_col(matrix1, line, matrix2, col, &(result->matrix[result->count_of_columns * line + col]));
        }
    }
}
