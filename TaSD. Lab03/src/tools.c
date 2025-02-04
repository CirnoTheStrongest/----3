#include "tools.h"

int str_to_int(char *str, int *num)
{
    if (!strlen(str))
        return EXIT_FAILURE;

    if (str[strlen(str) - 1] == '\n')
        str[strlen(str) - 1] = '\0';
    
    if (!strlen(str))
        return EXIT_FAILURE;

    for (size_t i = 0; i < strlen(str); i++)
    {
        if (!isdigit(str[i]))
            return EXIT_FAILURE;
    }

    *num = atoi(str);
    return EXIT_SUCCESS;
}

int find_max(int *array, size_t len)
{
    int max = array[0];
    
    for (size_t i = 1; i < len; i++)
        if (array[i] > max)
            max = array[i];

    return max;
}

int read_array(int *array, size_t *size, FILE *filename)
{
    *size = 0;
    char next_char = ' ';

    while (next_char != '\n' && !feof(filename))
    {
        if (fscanf(filename, "%d", &(array[*size])) != 1)
            return EXIT_FAILURE;
            
        (*size)++;
        next_char = fgetc(filename);
    }

    return EXIT_SUCCESS;
}

void print_array(int *array, size_t size)
{
    for (size_t i = 0; i < size; i++)
        printf("%d ", array[i]);
    puts("");
}

void print_array_in_file(int *array, size_t size, FILE *filename)
{
    for (size_t i = 0; i < size - 1; i++)
        fprintf(filename, "%d ", array[i]);
    fprintf(filename, "%d\n", array[size - 1]);
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
