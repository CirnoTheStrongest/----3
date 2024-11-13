#ifndef TOOLS_H
#define TOOLS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "file.h"

int find_max(int *array, size_t len);

void print_array(int *array, size_t size);

int insert_in_array(int *array, size_t *len, int value, size_t position);

void swap(void *l, void *r, size_t size);

int delete_from_array(int *array, size_t *len, size_t position);

int read_array(int *array, size_t *size, FILE *filename);

void print_array_in_file(int *array, size_t size, FILE *filename);

#endif
