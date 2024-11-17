#include "file.h"

int init_file_for_read(file_t *file)
{
    char str[200];
    puts("Введите имя файла для ввода:");
    
    if (!fgets(str, sizeof(str), stdin))
        return EBADF;

    if (str[strlen(str) - 1] == '\n')
        str[strlen(str) - 1] = '\0';
        
    FILE *f;
    if ((f = fopen(str, "r")))
    {
        fclose(f);

        *file = malloc(strlen(str) * sizeof(char) + 1);

        strcpy(*file, str);
        return EXIT_SUCCESS;
    }

    return EBADF;
}

int init_file_for_write(file_t *file)
{
    char str[200];
    puts("Введите имя файла для вывода:");
    
    if (!fgets(str, sizeof(str), stdin))
        return EBADF;

    if (str[strlen(str) - 1] == '\n')
        str[strlen(str) - 1] = '\0';
        
    FILE *f;
    if ((f = fopen(str, "w")))
    {
        fclose(f);

        *file = malloc(strlen(str) * sizeof(char) + 1);

        strcpy(*file, str);
        return EXIT_SUCCESS;
    }

    return EBADF;
}
