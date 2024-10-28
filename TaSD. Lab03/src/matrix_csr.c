#include "matrix_csr.h"

// прочитать матрицу из файла в обычном виде как матрицу в csr виде
int read_matrix_csr(FILE *f, matrix_csr_t *matrix)
{
    int cur;
    char str[MAX_STR_LEN];
    int i = 0;
    int j = 0;

    matrix->A.size = 0;
    matrix->IA.size = 0;
    matrix->JA.size = 0;
    matrix->IA.values[0] = 0;

    while (fgets(str, sizeof(str), f))
    {
        j = 0;
        matrix->IA.values[matrix->IA.size + 1] = matrix->IA.values[matrix->IA.size];
        matrix->IA.size++;

        char *tmp = strtok(str, " \n");

        while (tmp)
        {
            cur = atoi(tmp);

            if (cur)
            {
                matrix->A.values[matrix->A.size++] = cur;
                matrix->IA.values[matrix->IA.size]++;
                matrix->JA.values[matrix->JA.size++] = j;
            }

            j++;
            tmp = strtok(NULL, " \n");
        }
        i++;
    }

    if (!feof(f))
        return EIO;

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
            if (j == *cur_elem_in_JA && cur_elem < *cur_elem_in_IA)
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

// Функция для печати матрицы в виде её составляющих
void print_matrix_csr_vectors(matrix_csr_t *matrix)
{
    puts("Массив.");

    printf("Значения:  ");
    print_array(matrix->A.values, matrix->A.size);

    printf("Массив JA: ");
    print_array(matrix->JA.values, matrix->JA.size);

    printf("Массив IA: ");
    print_array(matrix->IA.values, matrix->IA.size);
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
            if (*position == col)
            {
                delete_from_array(matrix->JA.values, matrix->JA.size, position - &(matrix->JA.values[0]));
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

// Функция умножения матрицы csr на матрицу csc
void multiply_by_csc_matrix(matrix_csr_t *matrix_csr, matrix_csc_t *matrix_csc)
{
    
}
