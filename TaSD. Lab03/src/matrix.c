#include "matrix.h"

// матрица хранится как одномерный массив

int init_matrix(matrix_t *matrix, size_t count_of_lines, size_t count_of_cols)
{
    matrix->matrix = malloc(sizeof(int) * (count_of_lines * count_of_cols + 2));
    matrix->count_of_lines = count_of_lines;
    matrix->count_of_columns = count_of_cols;

    return EXIT_SUCCESS;
}

void free_matrix(matrix_t *matrix)
{
    free(matrix->matrix);
    matrix->count_of_lines = 0;
    matrix->count_of_columns = 0;
}

void print_matrix(matrix_t *matrix)
{
    printf("%lu %lu\n", matrix->count_of_lines, matrix->count_of_columns);
    for (size_t i = 0; i < matrix->count_of_lines; i++)
    {
        for (size_t j = 0; j < matrix->count_of_columns; j++)
        {
            printf("%d ", *(matrix->matrix + i * matrix->count_of_columns + j));
        }
        printf("\n");
    }
}

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

    init_matrix(matrix, n, m);
    
    for (size_t i = 0; i < n; i++)
    {
        for (size_t j = 0; j < m; j++)
        {
            if (!fscanf(f, "%d", matrix->matrix + m * i + j))
            {
                fclose(f);
                free_matrix(matrix);
                return EIO;
            }
        }
    }

    fclose(f);
    return EXIT_SUCCESS;
}

size_t get_size_of_matrix(matrix_t *matrix)
{
    return sizeof(*matrix) + sizeof(int) * (matrix->count_of_columns * matrix->count_of_lines);
}

int set_value(matrix_t *matrix, size_t line, size_t col, int value)
{
    if (line > matrix->count_of_lines - 1 || col > matrix->count_of_columns - 1)
        return ERANGE;

    matrix->matrix[line * matrix->count_of_columns + col] = value;
    return EXIT_SUCCESS;
}

int input_and_set_value(matrix_t *matrix)
{
    int line, col;
    int value;
    char buf[100];
    int rc;

    puts("Введите через пробел строку, столбец и значение, которое необходимо присвоить указанной ячейке:");
    if (!fgets(buf, sizeof(buf), stdin))
    {
        return EIO;
    }
    
    char *pch = strtok(buf, " \n");
    
    rc = str_to_int(pch, &line);
    pch = strtok(NULL, " \n");
    rc = str_to_int(pch, &col);
    pch = strtok(NULL, " \n");
    rc = str_to_int(pch, &value);
    pch = strtok(NULL, " \n");

    if (pch != NULL)
        return EIO;

    rc = set_value(matrix, line, col, value);
    if (rc)
        return rc;
    return EXIT_SUCCESS;
}
