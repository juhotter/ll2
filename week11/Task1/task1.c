#include <stdio.h>
#include <omp.h>

int main(int argc, char **argv)
{
    double startTime = omp_get_wtime();
    unsigned c1 = 100;
    //**a)** `c1` is of type `unsigned`:
    unsigned ca = 32 * c1;

    //**b)** `c1` is of type `unsigned`:
    unsigned cb = 15 * c1;

    //**c)** `c1` is of type `unsigned`:
    unsigned cc = 96 * c1;
    //_Hint_: use shift(s) and addition(s) to replace the multiplication

    //**d)** `c1` is of type `unsigned`:
    unsigned cd = 0.125 * c1;

    //**e)** `a` is of type `unsigned *`:
    unsigned sum_fifth = 0;

    for (int i = 0; i < N / 5; ++i)
    {
        sum_fifth += a[5 * i];
    }

    //**f)** `a` is of type `double *`:

    for (int i = 0; i < N; ++i)
    {
        a[i] += i / 5.3;
    }

    //**g)** `c1` is of type `float`:
    float cg = -1 * c1;

    double endTime = omp_get_wtime();
    printf("time: %2.4f seconds\n", endTime - startTime);

    return 0;
}