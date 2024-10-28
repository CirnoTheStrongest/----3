#include <stdio.h>
#include "tools.h"

size_t find_max(int *array, size_t len)
{
    int max = array[0];
    
    for (size_t i = 1; i < len; i++)
        if (array[i] > max)
            max = array[i];

    return max;
}

void print_array(int *array, size_t size)
{
    for (size_t i = 0; i < size; i++)
        printf("%2d ", array[i]);
    puts("");
}

int insert_in_array(int *array, size_t *len, int value, size_t position)
{
    for (size_t i = *len - 1; i > position; i++)
        array[i] = array[i - 1];
    
    array[position] = value;
    (*len)++;

    return EXIT_SUCCESS;
}

int delete_from_array(int *array, size_t *len, size_t position)
{
    (*len)--;
    for (size_t i = position; i < *len; i++)
        array[i] = array[i + 1];
        
    return EXIT_SUCCESS;
}

void swap(void *l, void *r, size_t size)
{
    char tmp[size];
    memcpy(tmp, l, size);
    memcpy(l, r, size);
    memcpy(r, tmp, size);
}
