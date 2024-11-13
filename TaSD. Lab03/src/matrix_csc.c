#include "matrix_csc.h"

int read_matrix_csc_as_matrix(file_t filename, matrix_csc_t *matrix_csc)
{
    int rc;
    matrix_t matrix;

    if ((rc = read_matrix(filename, &matrix)))
        return rc;
    if ((rc = convert_matrix_to_csc(&matrix, matrix_csc)))
        return rc;

    return EXIT_SUCCESS;
}

int convert_matrix_to_csc(matrix_t *matrix, matrix_csc_t *matrix_csc)
{
    matrix_csc->A.size = 0;
    matrix_csc->JA.size = 0;
    matrix_csc->IA.size = 0;
    matrix_csc->JA.values[0] = 0;

    for (size_t i = 0; i < matrix->count_of_columns; i++)
    {
        matrix_csc->JA.values[matrix_csc->JA.size + 1] = matrix_csc->JA.values[matrix_csc->JA.size];
        matrix_csc->JA.size++;

        for (size_t j = 0; j < matrix->count_of_lines; j++)
        {
            if (*(matrix->matrix + j * matrix->count_of_columns + i))
            {
                matrix_csc->A.values[matrix_csc->A.size++] = *(matrix->matrix + j * matrix->count_of_columns + i);
                matrix_csc->JA.values[matrix_csc->JA.size]++;
                matrix_csc->IA.values[matrix_csc->IA.size++] = j;
            }
        }
    }

    return EXIT_SUCCESS;
}

// печать матрицы csr в виде матрицы
void print_matrix_csc(matrix_csc_t *matrix)
{
    // Текущий ненулевой элемент матрицы
    int *cur_elem_in_A = &(matrix->A.values[0]);

    // Текущий элемент в массиве JA
    int *cur_elem_in_IA = &(matrix->IA.values[0]);

    // Текущий элемент в массиве IA
    int *cur_elem_in_JA = &(matrix->JA.values[1]);

    size_t max = find_max(matrix->IA.values, matrix->IA.size);

    // Текущий элемент матрицы
    size_t cur_elem = 0;
    
    for (size_t i = 0; i < matrix->JA.size; i++)
    {
        for (size_t j = 0; j <= max; j++)
        {
            if (j == (size_t) *cur_elem_in_IA && cur_elem < (size_t) *cur_elem_in_JA)
            {
                printf("%d ", *cur_elem_in_A);
                cur_elem_in_A++;
                cur_elem_in_IA++;
                cur_elem++;
            }
            else
            {
                printf("0 ");
            }
        }
        cur_elem_in_JA++;
        puts("");
    }
}

int read_matrix_csc(matrix_csc_t *matrix_csc, file_t filename)
{
    FILE *f = fopen(filename, "r");

    read_array(matrix_csc->A.values, &(matrix_csc->A.size), f);
    read_array(matrix_csc->IA.values, &(matrix_csc->IA.size), f);
    read_array(matrix_csc->JA.values, &(matrix_csc->JA.size), f);

    fclose(f);
    return EXIT_SUCCESS;
}

// Функция для печати матрицы в виде её составляющих
void print_matrix_csc_vectors(matrix_csc_t *matrix)
{
    puts("Массив.");

    printf("Значения:  ");
    print_array(matrix->A.values, matrix->A.size);

    printf("Массив IA: ");
    print_array(matrix->IA.values, matrix->IA.size);

    printf("Массив JA: ");
    print_array(matrix->JA.values, matrix->JA.size + 1);
}

void print_matrix_csc_vectors_in_file(matrix_csc_t *matrix, file_t filename)
{
    FILE *f = fopen(filename, "w");

    print_array_in_file(matrix->A.values, matrix->A.size, f);

    print_array_in_file(matrix->IA.values, matrix->IA.size, f);

    print_array_in_file(matrix->JA.values, matrix->JA.size + 1, f);

    fclose(f);
}

// не проверено
int set_value_csc(matrix_csc_t *matrix, int value, size_t line, size_t col)
{
    // если value не равно нулю
    if (value)
    {
        // изменяем значения количества ненулевых элементов в предшествующих текущей строке строках на +1
        for (size_t i = col + 1; i < matrix->JA.size; i++)
            matrix->JA.values[i]++;

        // вставляем в массив столбцов новое значение если оно не 0
        int *position = &(matrix->IA.values[matrix->JA.values[col]]);
        int *next_line = &(matrix->IA.values[matrix->JA.values[col + 1]]);
        insert_in_array(matrix->IA.values, &(matrix->IA.size), line, matrix->JA.values[col]);
        
        // ставим значения столбцов в строке по порядку
        while (*position > *(position + 1) && position < next_line)
        {
            swap(position, position + 1, sizeof(int));
            position++;
        }

        // вставляем в массив значений новое значение
        insert_in_array(matrix->A.values, &(matrix->A.size), value, position - &(matrix->IA.values[0]));
    }
    else // если value равно нулю
    {
        // изменяем значения количества ненулевых элементов в предшествующих текущей строке строках на +1
        for (size_t i = col + 1; i < matrix->JA.size; i++)
            matrix->JA.values[i]--;

        // удаляем из массива столбцов соответствующее значение
        int *position = &(matrix->IA.values[matrix->JA.values[col]]);
        int *next_line = &(matrix->IA.values[matrix->JA.values[col + 1]]);
        while (position < next_line)
        {
            if (*position == (int) line)
            {
                delete_from_array(matrix->IA.values, &(matrix->IA.size), position - &(matrix->IA.values[0]));
                break;
            }
            position++;
        }

        // удаляем из массива значений соответствующее значение
        delete_from_array(matrix->A.values, &(matrix->A.size), position - &(matrix->IA.values[0]));
    }
    
    return EXIT_SUCCESS;
}

// Функция возвращает процент заполненности csr матрицы ненулевыми значениями
int get_sparceness_percent_csc(matrix_csc_t *matrix, size_t *percent)
{
    size_t amount_of_lines = matrix->IA.size;
    size_t amount_of_columns = find_max(matrix->IA.values, matrix->IA.size);
    size_t amount_of_non_zero_elements = matrix->A.size;

    *percent = amount_of_non_zero_elements * 100 / (amount_of_columns * amount_of_lines); 
    return EXIT_SUCCESS;
}
