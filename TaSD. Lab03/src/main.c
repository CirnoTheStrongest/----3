#include <stdlib.h>
#include <errno.h>
#include "interface.h"
#include "file.h"
#include "matrix.h"
#include "matrix_csr.h"
#include "matrix_csc.h"
#include "matrix_multiplication.h"

int main(void)
{
    int rc;
    int action;
    matrix_t matrix1;
    matrix_t matrix2;
    matrix_csc_t matrix_csc;
    matrix_csr_t matrix_csr;

    while (1)
    {
        show_menu();
        get_action(&action);
        rc = do_action(action, &matrix1, &matrix2, &matrix_csc, &matrix_csr);
        if (rc) 
            print_error_message(rc);
    }

    return EXIT_SUCCESS;
}
