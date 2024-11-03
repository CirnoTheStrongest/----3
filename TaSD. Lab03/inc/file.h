#ifndef FILE_H
#define FILE_H

#include <errno.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef char *file_t;

int init_file_for_read(file_t *file, const char *str);
int init_file_for_write(file_t *file, const char *str);

#endif
