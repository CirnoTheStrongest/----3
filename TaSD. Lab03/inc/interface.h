#ifndef INTERFACE_H
#define INTERFACE_H

#include <stdio.h>
#include <stdlib.h>
#include "matrix.h"
#include "matrix_csc.h"
#include "matrix_csr.h"
#include "matrix_multiplication.h"

#define INCORRECT_ACT_MSG "Некорректный номер действия!"
#define EXIT_MSG "Завершение программы..."

// Функция, которая выводит меню программы
void show_menu(void);

// Функция для получения номера действия
int get_action(int *action);

// Функция, реализующая действие, выбранное пользователем
int do_action(int action, matrix_t *matrix1, matrix_t *matrix2, matrix_csc_t *matrix_csc, matrix_csr_t *matrix_csr);

#endif
