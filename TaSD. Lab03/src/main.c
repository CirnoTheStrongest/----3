#include <stdlib.h>
#include <errno.h>
#include "matrix_csr.h"

int main(void)
{
    matrix_csr_t matrix;
    FILE *f = fopen("matrix.txt", "r");

    read_matrix_csr(f, &matrix);
    print_matrix_csr(&matrix);
    print_matrix_csr_vectors(&matrix);

    fclose(f);
    return EXIT_SUCCESS;
}