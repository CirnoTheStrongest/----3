#include "interface.h"

void show_menu(void)
{
    puts("1. Считать первую матрицу в обычном виде из файла.");
    puts("2. Считать вторую матрицу в обычном виде из файла.");
    puts("3. Считать матрицу в обычном виде из файла и перевести в csc-матрицу.");
    puts("4. Считать матрицу в обычном виде из файла и перевести в csr-матрицу.");
    puts("5. Считать csc-матрицу из файла.");
    puts("6. Считать csr-матрицу из файла.");
    puts("7. Умножить csc-матрицу на csr-матрицу."); // результат в файл, не изменяем изначальные матрицы
    puts("8. Умножить csr-матрицу на csc-матрицу."); // результат в файл, не изменяем изначальные матрицы
    puts("9. Уммножить матрицы в обычном виде."); // требуется указать порядок матриц
    puts("10. Исследование времени умножения матриц.");
    puts("11. Выход.");
}

int get_action(int *action)
{
    puts("Введите номер действия от 1 до 11 включительно:");
    if (scanf("%d", action) != 1)
    {
        puts(INCORRECT_ACT_MSG);
        return EXIT_FAILURE;
    }

    if (*action < 1 || *action > 11)
    {
        puts(INCORRECT_ACT_MSG);
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}

int do_action(int action, matrix_t *matrix1, matrix_t *matrix2, matrix_csc_t *matrix_csc, matrix_csr_t *matrix_csr)
{
    file_t filename;
    matrix_csc_t result_csc;
    matrix_t result_matrix;

    switch (action)
    {
    case 1:
        init_file_for_read(&filename);
        read_matrix(filename, matrix1);
        free(filename);
        break;
    case 2:
        init_file_for_read(&filename);
        read_matrix(filename, matrix2);
        free(filename);
        break;
    case 3:
        init_file_for_read(&filename);
        read_matrix_csc_as_matrix(filename, matrix_csc);
        free(filename);
        break;
    case 4:
        init_file_for_read(&filename);
        read_matrix_csr_as_matrix(filename, matrix_csr);
        free(filename);
        break;
    case 5:
        init_file_for_read(&filename);
        read_matrix_csc(matrix_csc, filename);
        free(filename);
        break;
    case 6:
        init_file_for_read(&filename);
        read_matrix_csr(matrix_csr, filename);
        free(filename);
        break;
    case 7:
        init_file_for_write(&filename);

        multiply_csc_by_csr_matrix(matrix_csc, matrix_csr, &result_csc);
        print_matrix_csc_vectors_in_file(&result_csc, filename);

        free(filename);
        break;
    case 8:
        init_file_for_write(&filename);

        multiply_csr_by_csc_matrix(matrix_csr, matrix_csc, &result_csc);
        print_matrix_csc_vectors_in_file(&result_csc, filename);

        free(filename);
        break;
    case 9:
        init_file_for_write(&filename);

        multiply_matrix_by_matrix(matrix1, matrix2, &result_matrix);
        print_matrix_in_file(&result_matrix, filename);

        free(filename);
        break;
    case 10:
        //test_multiplication();
        //
        break;
    case 11:
        puts(EXIT_MSG);
        exit(EXIT_SUCCESS);
    default:
        break;
    }
    return EXIT_SUCCESS;
}
