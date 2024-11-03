#include "file.h"

int init_file_for_read(file_t *file, const char *str)
{
    if (str == NULL)
        return EBADF;
        
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

int init_file_for_write(file_t *file, const char *str)
{
    if (str == NULL)
        return EBADF;
        
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
