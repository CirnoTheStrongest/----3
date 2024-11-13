#include <stdio.h>

int main(void)
{
    int num;
    char ch = ' ';
    FILE *f = fopen("output.txt", "r");

    while (ch != '\n')
    {
        fscanf(f, "%d", &num);
        ch = fgetc(f);
        printf("%d_%c\n", num, ch);
    }

    fclose(f);
}