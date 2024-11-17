#include "interface.h"

void show_menu(void)
{
    puts("1. Считать первую матрицу в обычном виде из файла.");
    puts("2. Вывести первую матрицу в консоль.");
    puts("3. Добавить/изменить значение ячейки первой матрицы.");
    puts("4. Считать вторую матрицу в обычном виде из файла.");
    puts("5. Вывести вторую матрицу в консоль.");
    puts("6. Добавить/изменить значение ячейки второй матрицы.");
    puts("7. Считать матрицу в обычном виде из файла и перевести в csc-матрицу.");
    puts("8. Считать матрицу в обычном виде из файла и перевести в csr-матрицу.");
    puts("9. Считать csc-матрицу из файла.");
    puts("10. Считать csr-матрицу из файла.");
    puts("11. Вывести csc-матрицу в консоль.");
    puts("12. Вывести csr-матрицу в консоль.");
    puts("13. Вывести csc-матрицу в консоль в виде матрицы.");
    puts("14. Вывести csr-матрицу в консоль в виде матрицы.");
    puts("15. Добавить/изменить значение ячейки csc матрицы.");
    puts("16. Добавить/изменить значение ячейки csr матрицы.");
    puts("17. Умножить csc-матрицу на csr-матрицу."); // результат в файл, не изменяем изначальные матрицы
    puts("18. Умножить csr-матрицу на csc-матрицу."); // результат в файл, не изменяем изначальные матрицы
    puts("19. Уммножить матрицы в обычном виде."); // требуется указать порядок матриц
    puts("20. Исследование времени умножения матриц.");
    puts("21. Выход.");
}

int get_action(int *action)
{
    char buf[200];
    puts("Введите номер действия от 1 до 21 включительно:");
    if (!fgets(buf, sizeof(buf), stdin))
    {
        puts(INCORRECT_ACT_MSG);
        return EXIT_FAILURE;
    }

    str_to_int(buf, action);

    if (*action < 1 || *action > 21)
    {
        puts(INCORRECT_ACT_MSG);
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}

int do_action(int action, matrix_t *matrix1, matrix_t *matrix2, matrix_csc_t *matrix_csc, matrix_csr_t *matrix_csr)
{
    int rc;
    file_t filename;
    matrix_csc_t result_csc;
    matrix_t result_matrix;

    switch (action)
    {
    case 1:
        // инициализация файла
        if ((rc = init_file_for_read(&filename)))
            return rc;

        // чтение матрицы из файла
        if ((rc = read_matrix(filename, matrix1)))
        {
            free(filename);
            return rc;
        }

        // освобождение файловой переменной
        free(filename);
        break;
    case 2:
        print_matrix(matrix1);
        break;
    case 3:
        if ((rc = input_and_set_value(matrix1)))
            return rc;
        break;
    case 4:
        // инициализация файла
        if ((rc = init_file_for_read(&filename)))
            return rc;

        // чтение матрицы из файла
        if ((rc = read_matrix(filename, matrix2)))
        {
            free(filename);
            return rc;
        }

        // освобождение файловой переменной
        free(filename);
        break;
    case 5:
        print_matrix(matrix2);
        break;
    case 6:
        if ((rc = input_and_set_value(matrix2)))
            return rc;
        break;
    case 7:
        // инициализация файловой переменной
        if ((rc = init_file_for_read(&filename)))
            return rc;

        // чтение матрицы из файла
        if ((rc = read_matrix_csc_as_matrix(filename, matrix_csc)))
        {
            free(filename);
            return rc;
        }

        // освобождение файловой переменной
        free(filename);
        break;
    case 8:
        // инициализация файловой переменной
        if ((rc = init_file_for_read(&filename)))
            return rc;

        // чтение матрицы из файла
        if ((rc = read_matrix_csr_as_matrix(filename, matrix_csr)))
        {
            free(filename);
            return rc;
        }

        // освобождение файловой переменной
        free(filename);
        break;
    case 9:
        // инициализация файловой переменной
        if ((rc = init_file_for_read(&filename)))
            return rc;

        // чтение матрицы из файла
        if ((rc = read_matrix_csc(matrix_csc, filename)))
        {
            free(filename);
            return rc;
        }

        // освобождение файловой переменной
        free(filename);
        break;
    case 10:
        // инициализация файловой переменной
        if ((rc = init_file_for_read(&filename)))
            return rc;

        // чтение матрицы из файла
        if ((rc = read_matrix_csr(matrix_csr, filename)))
        {
            free(filename);
            return rc;
        }

        // освобождение файловой переменной
        free(filename);
        break;
    case 11:
        print_matrix_csc_vectors(matrix_csc);
        break;
    case 12:
        print_matrix_csr_vectors(matrix_csr);
        break;
    case 13:
        print_matrix_csc(matrix_csc);
        break;
    case 14:
        print_matrix_csr(matrix_csr);
        break;
    case 15:
        if ((rc = input_and_set_value_csc(matrix_csc)))
            return rc;
        break;
    case 16:
        if ((rc = input_and_set_value_csr(matrix_csr)))
            return rc;
        break;
    case 17:
        // инициализация файла для чтения
        if ((rc = init_file_for_write(&filename)))
            return rc;

        if ((rc = multiply_csc_by_csr_matrix(matrix_csc, matrix_csr, &result_csc)))
        {
            free(filename);
            return rc;
        }

        print_matrix_csc_vectors_in_file(&result_csc, filename);

        // освобождение файловой переменной
        free(filename);
        break;
    case 18:
        // инициализация файла для чтения
        if ((rc = init_file_for_write(&filename)))
            return rc;

        if ((rc = multiply_csr_by_csc_matrix(matrix_csr, matrix_csc, &result_csc)))
        {
            free(filename);
            return rc;
        }

        print_matrix_csc_vectors_in_file(&result_csc, filename);

        // освобождение файловой переменной
        free(filename);
        break;
    case 19:
        // инициализация файла для чтения
        if ((rc = init_file_for_write(&filename)))
            return rc;

        if ((rc = multiply_matrix_by_matrix(matrix1, matrix2, &result_matrix)))
        {
            free(filename);
            return rc;
        }

        print_matrix_in_file(&result_matrix, filename);

        // освобождение файловой переменной
        free(filename);
        break;
    case 20:
        test_multiplication();
        break;
    case 21:
        puts(EXIT_MSG);
        exit(EXIT_SUCCESS);
    default:
        break;
    }

    return EXIT_SUCCESS;
}

void print_error_message(int rc)
{
    switch (rc)
    {
    case EBADF:
        puts("Ошибка при чтении файла!");
        break;
    case EIO:
        puts("Некорректный ввод данных.");
        break;
    case ERANGE:
        puts("Выход за диапазон.");
        break;
    case ENOMEM:
        puts("Ошибка выделения памяти.");
        break;
    case EINVAL:
        puts("Умножение несогласованных матриц невозможно.");
        break;
    default:
        puts("Непредвиденная ошибка!");
        break;
    }
}
