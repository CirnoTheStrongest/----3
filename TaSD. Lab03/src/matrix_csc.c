#include "matrix_csc.h"

// Функция инициализации матрицы csc
int init_matrix_csc(matrix_csc_t *matrix_csc, size_t initial_A_size, size_t initial_JA_size)
{
    int rc;

    rc = init_vector(&(matrix_csc->A), initial_A_size);
    if (rc)
        return rc;
    rc = init_vector(&(matrix_csc->IA), initial_A_size);
    if (rc)
        return rc;
    rc = init_vector(&(matrix_csc->JA), initial_JA_size);
    if (rc)
        return rc;

    return EXIT_SUCCESS;
}

// Функция проверки, заполнены ли векторы матрицы csc
int is_matrix_csc_full(matrix_csc_t *matrix_csc)
{
    if (is_full(&(matrix_csc->A)))
        return 1;
    if (is_full(&(matrix_csc->IA)))
        return 1;
    if (is_full(&(matrix_csc->JA)))
        return 1;
    
    return 0;
}

// Функция реаллоцирования памяти для матрицы csc
int realloc_matrix_csc(matrix_csc_t *matrix_csc)
{
    int rc;

    if (is_full(&(matrix_csc->A)))
    {
        rc = realloc_vector(&(matrix_csc->A), matrix_csc->A.max_capacity * 2);
        if (rc)
            return rc;
        rc = realloc_vector(&(matrix_csc->IA), matrix_csc->IA.max_capacity * 2);
        if (rc)
            return rc;
    }

    if (is_full(&(matrix_csc->JA)))
    {
        rc = realloc_vector(&(matrix_csc->JA), matrix_csc->JA.max_capacity * 2);
        if (rc)
            return rc;
    }

    return EXIT_SUCCESS;
}

// Функция чтения обычной матрицы из файла и ее перевода в csc матрицу
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

// Функция конвертирования обычной матрицы в матрицу csc
int convert_matrix_to_csc(matrix_t *matrix, matrix_csc_t *matrix_csc)
{
    int rc;
    rc = init_matrix_csc(matrix_csc, INITIAL_SIZE, matrix->count_of_columns);
    if (rc)
        return rc;
    matrix_csc->JA.values[0] = 0;

    for (size_t i = 0; i < matrix->count_of_columns; i++)
    {
        matrix_csc->JA.size++;

        if (is_matrix_csc_full(matrix_csc))
        {
            rc = realloc_matrix_csc(matrix_csc);
            if (rc)
                return rc;
        }

        matrix_csc->JA.values[matrix_csc->JA.size] = matrix_csc->JA.values[matrix_csc->JA.size - 1];

        for (size_t j = 0; j < matrix->count_of_lines; j++)
        {
            if (*(matrix->matrix + j * matrix->count_of_columns + i))
            {
                matrix_csc->A.values[matrix_csc->A.size++] = *(matrix->matrix + j * matrix->count_of_columns + i);
                matrix_csc->JA.values[matrix_csc->JA.size]++;
                matrix_csc->IA.values[matrix_csc->IA.size++] = j;

                if (is_matrix_csc_full(matrix_csc))
                {
                    rc = realloc_matrix_csc(matrix_csc);
                    if (rc)
                        return rc;
                }
            }
        }
    }

    return EXIT_SUCCESS;
}

// Функция печати матрицы csr в виде матрицы
void print_matrix_csc(matrix_csc_t *matrix)
{
    int max = find_max(matrix->IA.values, matrix->IA.size);

    int value;    
    for (int i = 0; i < max + 1; i++)
    {
        for (size_t j = 0; j < matrix->JA.size; j++)
        {
            value = 0;

            for (int index = matrix->JA.values[j]; index < matrix->JA.values[j + 1]; index++)
            {
                if (matrix->IA.values[index] == i)
                {
                    value = matrix->A.values[index];
                    break;
                }
            }

            printf("%d ", value);
        }
        puts("");
    }
}

int read_matrix_csc(matrix_csc_t *matrix_csc, file_t filename)
{
    FILE *f = fopen(filename, "r");

    read_vector_from_file(&(matrix_csc->A), f);
    read_vector_from_file(&(matrix_csc->IA), f);
    read_vector_from_file(&(matrix_csc->JA), f);

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

        if (is_matrix_csc_full(matrix))
                    realloc_matrix_csc(matrix);
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

void free_matrix_csc(matrix_csc_t *matrix_csc)
{
    free(matrix_csc->A.values);
    free(matrix_csc->IA.values);
    free(matrix_csc->JA.values);

    matrix_csc->A.max_capacity = 0;
    matrix_csc->IA.max_capacity = 0;
    matrix_csc->JA.max_capacity = 0;
}

size_t get_size_of_matrix_csc(matrix_csc_t *matrix_csc)
{
    return sizeof(*matrix_csc)  + sizeof(int) * (matrix_csc->A.max_capacity + matrix_csc->IA.max_capacity + matrix_csc->JA.max_capacity);
}
