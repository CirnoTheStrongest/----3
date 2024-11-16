#include "matrix_csr.h"

int init_matrix_csr(matrix_csr_t *matrix_csr, size_t initial_A_size, size_t initial_IA_size)
{
    int rc;

    rc = init_vector(&(matrix_csr->A), initial_A_size);
    if (rc)
        return rc;
    rc = init_vector(&(matrix_csr->JA), initial_A_size);
    if (rc)
        return rc;
    rc = init_vector(&(matrix_csr->IA), initial_IA_size);
    if (rc)
        return rc;

    return EXIT_SUCCESS;
}

int is_matrix_csr_full(matrix_csr_t *matrix_csr)
{
    if (is_full(&(matrix_csr->A)))
        return 1;
    if (is_full(&(matrix_csr->JA)))
        return 1;
    if (is_full(&(matrix_csr->IA)))
        return 1;
    
    return 0;
}

int realloc_matrix_csr(matrix_csr_t *matrix_csr)
{
    int rc;

    if (is_full(&(matrix_csr->A)))
    {
        rc = realloc_vector(&(matrix_csr->A), matrix_csr->A.max_capacity * 2);
        if (rc)
            return rc;
        rc = realloc_vector(&(matrix_csr->JA), matrix_csr->JA.max_capacity * 2);
        if (rc)
            return rc;
    }

    if (is_full(&(matrix_csr->IA)))
    {
        rc = realloc_vector(&(matrix_csr->IA), matrix_csr->IA.max_capacity * 2);
        if (rc)
            return rc;
    }

    return EXIT_SUCCESS;
}

// прочитать матрицу из файла в обычном виде как матрицу в csr виде
int read_matrix_csr_as_matrix(file_t filename, matrix_csr_t *matrix_csr)
{
    int rc;
    matrix_t matrix;

    if ((rc = read_matrix(filename, &matrix)))
        return rc;
    if ((rc = convert_matrix_to_csr(&matrix, matrix_csr)))
        return rc;

    return EXIT_SUCCESS;
}

int convert_matrix_to_csr(matrix_t *matrix, matrix_csr_t *matrix_csr)
{
    int rc;
    rc = init_matrix_csr(matrix_csr, INITIAL_SIZE, matrix->count_of_lines);
    if (rc)
        return rc;
    matrix_csr->IA.values[0] = 0;

    for (size_t i = 0; i < matrix->count_of_lines; i++)
    {
        matrix_csr->IA.size++;

        if (is_matrix_csr_full(matrix_csr))
        {
            rc = realloc_matrix_csr(matrix_csr);
            if (rc)
                return rc;
        }

        matrix_csr->IA.values[matrix_csr->IA.size] = matrix_csr->IA.values[matrix_csr->IA.size - 1];

        for (size_t j = 0; j < matrix->count_of_columns; j++)
        {
            if (*(matrix->matrix + i * matrix->count_of_columns + j))
            {
                matrix_csr->A.values[matrix_csr->A.size++] = *(matrix->matrix + i * matrix->count_of_columns + j);
                matrix_csr->IA.values[matrix_csr->IA.size]++;
                matrix_csr->JA.values[matrix_csr->JA.size++] = j;

                if (is_matrix_csr_full(matrix_csr))
                {
                    rc = realloc_matrix_csr(matrix_csr);
                    if (rc)
                        return rc;
                }
            }
        }
    }
    return EXIT_SUCCESS;
}

// печать матрицы csr в виде матрицы
void print_matrix_csr(matrix_csr_t *matrix)
{
    // Текущий ненулевой элемент матрицы
    int *cur_elem_in_A = &(matrix->A.values[0]);

    // Текущий элемент в массиве JA
    int *cur_elem_in_JA = &(matrix->JA.values[0]);

    // Текущий элемент в массиве IA
    int *cur_elem_in_IA = &(matrix->IA.values[1]);

    size_t max = find_max(matrix->JA.values, matrix->JA.size);

    // Текущий элемент матрицы
    size_t cur_elem = 0;
    
    for (size_t i = 0; i < matrix->IA.size; i++)
    {
        for (size_t j = 0; j <= max; j++)
        {
            if ((j == (size_t) *cur_elem_in_JA && cur_elem < (size_t) *cur_elem_in_IA))
            {
                printf("%d ", *cur_elem_in_A);
                cur_elem_in_A++;
                cur_elem_in_JA++;
                cur_elem++;
            }
            else
            {
                printf("0 ");
            }
        }
        cur_elem_in_IA++;
        puts("");
    }
}

int read_matrix_csr(matrix_csr_t *matrix_csr, file_t filename)
{
    FILE *f = fopen(filename, "r");

    read_vector_from_file(&(matrix_csr->A), f);
    read_vector_from_file(&(matrix_csr->JA), f);
    read_vector_from_file(&(matrix_csr->IA), f);

    fclose(f);
    return EXIT_SUCCESS;
}

// Функция для печати матрицы в виде её составляющих
void print_matrix_csr_vectors(matrix_csr_t *matrix)
{
    puts("Массив.");

    printf("Значения:  ");
    print_array(matrix->A.values, matrix->A.size);

    printf("Массив JA: ");
    print_array(matrix->JA.values, matrix->JA.size);

    printf("Массив IA: ");
    print_array(matrix->IA.values, matrix->IA.size + 1);
}

void print_matrix_csr_vectors_in_file(matrix_csr_t *matrix, file_t filename)
{
    FILE *f = fopen(filename, "w");

    print_array_in_file(matrix->A.values, matrix->A.size, f);

    print_array_in_file(matrix->JA.values, matrix->JA.size, f);

    print_array_in_file(matrix->IA.values, matrix->IA.size + 1, f);

    fclose(f);
}

// не проверено
int set_value_csr(matrix_csr_t *matrix, int value, size_t line, size_t col)
{
    // если value не равно нулю
    if (value)
    {
        // изменяем значения количества ненулевых элементов в предшествующих текущей строке строках на +1
        for (size_t i = line + 1; i < matrix->IA.size; i++)
            matrix->IA.values[i]++;

        // вставляем в массив столбцов новое значение если оно не 0
        int *position = &(matrix->JA.values[matrix->IA.values[line]]);
        int *next_line = &(matrix->JA.values[matrix->IA.values[line + 1]]);
        insert_in_array(matrix->JA.values, &(matrix->JA.size), col, matrix->IA.values[line]);
        
        // ставим значения столбцов в строке по порядку
        while (*position > *(position + 1) && position < next_line)
        {
            swap(position, position + 1, sizeof(int));
            position++;
        }

        // вставляем в массив значений новое значение
        insert_in_array(matrix->A.values, &(matrix->A.size), value, position - &(matrix->JA.values[0]));

        if (is_matrix_csr_full(matrix))
            realloc_matrix_csr(matrix);
    }
    else // если value равно нулю
    {
        // изменяем значения количества ненулевых элементов в предшествующих текущей строке строках на +1
        for (size_t i = line + 1; i < matrix->IA.size; i++)
            matrix->IA.values[i]--;

        // удаляем из массива столбцов соответствующее значение
        int *position = &(matrix->JA.values[matrix->IA.values[line]]);
        int *next_line = &(matrix->JA.values[matrix->IA.values[line + 1]]);
        while (position < next_line)
        {
            if ((size_t) *position == col)
            {
                delete_from_array(matrix->JA.values, &(matrix->JA.size), position - &(matrix->JA.values[0]));
                break;
            }
            position++;
        }

        // удаляем из массива значений соответствующее значение
        delete_from_array(matrix->A.values, &(matrix->A.size), position - &(matrix->JA.values[0]));
    }
    
    return EXIT_SUCCESS;
}

// Функция возвращает процент заполненности csr матрицы ненулевыми значениями
int get_sparceness_percent_csr(matrix_csr_t *matrix, size_t *percent)
{
    size_t amount_of_lines = matrix->IA.size;
    size_t amount_of_columns = find_max(matrix->JA.values, matrix->JA.size);
    size_t amount_of_non_zero_elements = matrix->A.size;

    *percent = amount_of_non_zero_elements * 100 / (amount_of_columns * amount_of_lines); 
    return EXIT_SUCCESS;
}

void free_matrix_csr(matrix_csr_t *matrix_csr)
{
    free(matrix_csr->A.values);
    free(matrix_csr->JA.values);
    free(matrix_csr->IA.values);

    matrix_csr->A.max_capacity = 0;
    matrix_csr->JA.max_capacity = 0;
    matrix_csr->IA.max_capacity = 0;
}

size_t get_size_of_matrix_csr(matrix_csr_t *matrix_csr)
{
    return sizeof(*matrix_csr) + sizeof(int) * (matrix_csr->A.max_capacity + matrix_csr->IA.max_capacity + matrix_csr->JA.max_capacity);
}
