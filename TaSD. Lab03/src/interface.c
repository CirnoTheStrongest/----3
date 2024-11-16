#include "interface.h"

void show_menu(void)
{
    puts("1. Считать первую матрицу в обычном виде из файла.");
    puts("2. Вывести первую матрицу в консоль.");
    puts("3. Считать вторую матрицу в обычном виде из файла.");
    puts("4. Вывести вторую матрицу в консоль.");
    puts("5. Считать матрицу в обычном виде из файла и перевести в csc-матрицу.");
    puts("6. Считать матрицу в обычном виде из файла и перевести в csr-матрицу.");
    puts("7. Считать csc-матрицу из файла.");
    puts("8. Считать csr-матрицу из файла.");
    puts("9. Вывести csc-матрицу в консоль.");
    puts("10. Вывести csr-матрицу в консоль.");
    puts("11. Вывести csc-матрицу в консоль в виде матрицы.");
    puts("12. Вывести csr-матрицу в консоль в виде матрицы.");
    puts("13. Умножить csc-матрицу на csr-матрицу."); // результат в файл, не изменяем изначальные матрицы
    puts("14. Умножить csr-матрицу на csc-матрицу."); // результат в файл, не изменяем изначальные матрицы
    puts("15. Уммножить матрицы в обычном виде."); // требуется указать порядок матриц
    puts("16. Исследование времени умножения матриц.");
    puts("17. Выход.");
}

int get_action(int *action)
{
    char buf[200];
    puts("Введите номер действия от 1 до 11 включительно:");
    if (!fgets(buf, sizeof(buf), stdin))
    {
        puts(INCORRECT_ACT_MSG);
        return EXIT_FAILURE;
    }

    str_to_int(buf, action);

    if (*action < 1 || *action > 17)
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
        print_matrix(matrix1);
        break;
    case 3:
        init_file_for_read(&filename);
        read_matrix(filename, matrix2);
        free(filename);
        break;
    case 4:
        print_matrix(matrix2);
        break;
    case 5:
        init_file_for_read(&filename);
        read_matrix_csc_as_matrix(filename, matrix_csc);
        free(filename);
        break;
    case 6:
        init_file_for_read(&filename);
        read_matrix_csr_as_matrix(filename, matrix_csr);
        free(filename);
        break;
    case 7:
        init_file_for_read(&filename);
        read_matrix_csc(matrix_csc, filename);
        free(filename);
        break;
    case 8:
        init_file_for_read(&filename);
        read_matrix_csr(matrix_csr, filename);
        free(filename);
        break;
    case 9:
        print_matrix_csc_vectors(matrix_csc);
        break;
    case 10:
        print_matrix_csr_vectors(matrix_csr);
        break;
    case 11:
        print_matrix_csc(matrix_csc);
        break;
    case 12:
        print_matrix_csr(matrix_csr);
        break;
    case 13:
        init_file_for_write(&filename);

        multiply_csc_by_csr_matrix(matrix_csc, matrix_csr, &result_csc);
        print_matrix_csc_vectors_in_file(&result_csc, filename);

        free(filename);
        break;
    case 14:
        init_file_for_write(&filename);

        multiply_csr_by_csc_matrix(matrix_csr, matrix_csc, &result_csc);
        print_matrix_csc_vectors_in_file(&result_csc, filename);

        free(filename);
        break;
    case 15:
        init_file_for_write(&filename);

        multiply_matrix_by_matrix(matrix1, matrix2, &result_matrix);
        print_matrix_in_file(&result_matrix, filename);

        free(filename);
        break;
    case 16:
        test_multiplication();
        //
        break;
    case 17:
        puts(EXIT_MSG);
        exit(EXIT_SUCCESS);
    default:
        break;
    }
    return EXIT_SUCCESS;
}
