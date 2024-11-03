#include <stdlib.h>
#include <errno.h>
#include "file.h"
#include "matrix.h"
#include "matrix_csr.h"

int main(void)
{
    int rc;
    matrix_t matrix;

    file_t input_file;
    init_file_for_read(&input_file, "matrix.txt");

    if ((rc = read_matrix(input_file, &matrix)))
        return rc;

    file_t output_file;
    init_file_for_write(&output_file, "output.txt");

    print_matrix(output_file, &matrix);

    return EXIT_SUCCESS;
}