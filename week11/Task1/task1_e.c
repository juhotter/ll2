#include <stdio.h>
#include <omp.h>

#define N 1000

int main(int argc, char **argv)
{
    double startTime = omp_get_wtime();

    unsigned val = 5;
    unsigned *a = &val;
    //**e)** `a` is of type `unsigned *`:
    unsigned sum_fifth = 0;
    for (int i = 0; i < N / 5; ++i)
    {
        sum_fifth += a[5 * i];
    }

    double endTime = omp_get_wtime();
    double time = endTime - startTime;
    printf("result: %d\n", sum_fifth);
    printf("time * 10000000: %f seconds\n", time * 10000000);

    return 0;
}