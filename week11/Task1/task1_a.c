#include <stdio.h>
#include <omp.h>

int main(int argc, char **argv)
{
    double startTime = omp_get_wtime();

    unsigned c1 = 9999999;
    //**a)** `c1` is of type `unsigned`:
    //unsigned ca = 32 * c1;
    //replace multiplication by 32 to shift left by 5
    unsigned ca = c1 << 5;

    double endTime = omp_get_wtime();
    double time = endTime - startTime;
    printf("result: %d\n", ca);
    printf("time * 10000000: %f seconds\n", time * 10000000);

    return 0;
}
