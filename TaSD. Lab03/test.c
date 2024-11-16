#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    int zeros = 0;
    int iters = 1000;
    double result;
    int cur;

    for (int i = 0; i < iters; i++)
    {
        cur = rand() % 100;
        if (cur == 0)
            zeros++;
    }

    result = (double) zeros / iters;
    printf("%lf\n", result);

    return 0;
}